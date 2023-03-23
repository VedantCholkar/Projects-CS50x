import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    user_id = session["user_id"]
    row = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = row[0]["cash"]

    rows = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0", user_id)

    stocks = []  # Stores dictionaries
    total_value = 0

    for row in rows:  # Adds parameters to a dictionary
        stock = {}
        stock["symbol"] = row["symbol"]
        stock["shares"] = row["total_shares"]
        stock["price"] = lookup(stock["symbol"])["price"]
        stock["value"] = stock["shares"] * stock["price"]
        stock["name"] = lookup(stock["symbol"])["name"]
        stocks.append(stock)
        total_value += stock["value"]
        stock["price"] = usd(stock["price"])
        stock["value"] = usd(stock["value"])

    return render_template("index.html", stocks=stocks, cash=usd(cash), total_value=usd(total_value + cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    else:
        if not request.form.get("symbol") or not request.form.get("shares"):
            return apology("Missing parameters")

        stock_info = lookup(request.form.get("symbol"))  # Gets symbol
        shares = request.form.get("shares")
        cash = db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"])

        if not stock_info:
            return apology("Not a valid symbol")

        if shares.isnumeric() == False:
            return apology("Not a valid number")

        shares = int(shares)

        if shares < 1:
            return apology("Not valid amout of shares")

        if (stock_info["price"] * shares) > int(cash[0]["cash"]):
            return apology("Not enough cash")

        # Adds into transactions

        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, transacted) VALUES (?, ?, ?, ?, datetime('now'))",
            session["user_id"],
            stock_info["symbol"],
            shares,
            stock_info["price"],
        )

        # Updates cash

        db.execute(
            "UPDATE users SET cash = cash - ? WHERE id = ?",
            shares * stock_info["price"],
            session["user_id"],
        )

        # Checks if stock exists

        row = db.execute(
            "SELECT * FROM holdings WHERE user_id = ? AND symbol = ?",
            session["user_id"],
            stock_info["symbol"],
        )

        if not row:
            db.execute(
                "INSERT INTO holdings (user_id, symbol, shares) VALUES (?, ?, ?)",
                session["user_id"],
                stock_info["symbol"],
                shares,
            )

        else:
            db.execute(
                "UPDATE holdings SET shares = shares + ? WHERE user_id = ? AND symbol = ?",
                shares,
                session["user_id"],
                stock_info["symbol"],
            )

        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    transactions = db.execute(
        "SELECT symbol, shares, price, transacted FROM transactions WHERE user_id = ?", session["user_id"])

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get(
                "username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")

    else:

        if not request.form.get("symbol"):
            return apology("Missing symbol")

        stock_info = lookup(request.form.get("symbol"))

        if not stock_info:
            return apology("Not a valid symbol")

        return render_template(
            "quoted.html",
            name=stock_info["name"],
            price=usd(stock_info["price"]),
            symbol=stock_info["symbol"],
        )


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        password_con = request.form.get("confirmation")

        if not username or not password or not password_con:
            return apology("All fields required")

        if password != password_con:
            return apology("Passwords do not match")

        for user in db.execute("SELECT username FROM users"):
            if user["username"] == username:
                return apology("Username taken")

        password = generate_password_hash(password)

        db.execute(
            "INSERT INTO users (username, hash) VALUES(?, ?)", username, password
        )

        rows = db.execute("SELECT id FROM users WHERE username = ?", username)
        session["user_id"] = rows[0]["id"]

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        num_shares = request.form.get("shares")
        stock_info = lookup(symbol)

        if not symbol or not num_shares:
            return apology("Missing parameters")
        if symbol != db.execute("SELECT symbol FROM holdings WHERE user_id = ?", session["user_id"])[0]["symbol"]:
            return apology("No shares owned of company")

        shares = db.execute(
            "SELECT shares FROM holdings WHERE symbol = ?", symbol)

        if num_shares.isnumeric() == False:
            return apology("Not a valid number")

        num_shares = int(num_shares)
        if num_shares < 1:
            return apology("Must be a valid amount of shares")
        if not shares or shares[0]["shares"] < num_shares:
            return apology("Not enough shares to sell")

        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, transacted) VALUES (?, ?, ?, ?, datetime('now'))",
            session["user_id"],
            stock_info["symbol"],
            -num_shares,
            stock_info["price"],
        )

        db.execute(
            "UPDATE users SET cash = cash + ? WHERE id = ?",
            num_shares * stock_info["price"],
            session["user_id"],
        )

        db.execute(
            "UPDATE holdings SET shares = shares - ? WHERE user_id = ? AND symbol = ?",
            num_shares,
            session["user_id"],
            symbol,
        )

        db.execute("DELETE FROM holdings WHERE shares = 0")

        return redirect("/")

    else:
        return render_template("sell.html", stocks=db.execute("SELECT symbol FROM holdings WHERE user_id = ?", session["user_id"]))


@app.route("/cash", methods=["GET", "POST"])
@login_required
def cash():
    if request.method == "POST":
        cash = request.form.get("cash")

        if not cash:
            return apology("Missing cash")
        if cash.isnumeric() == "False":
            return apology("Not a valid number")

        cash = int(cash)

        if cash < 1 or cash > 10000000:
            return apology("Not a valid amount")

        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?",
                   cash, session["user_id"])

        return redirect("/")

    else:
        return render_template("cash.html")


# This was a good problem as the end result is a fully functioning web app
# The progress I have made is astounding
# Thanks to Harvard and David Malan for making this course
# And thanks to whoever is reading this
