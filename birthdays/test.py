import os

from cs50 import SQL

db = SQL("sqlite:///birthdays.db")
birthdays = db.execute("SELECT * FROM birthdays")

for id in birthdays:
    print(id['name'])

# print(birthdays[])