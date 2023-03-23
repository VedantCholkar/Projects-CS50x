from cs50 import get_string

while True:
    user_input = get_string("Input: ")
    if len(user_input) > 0:
        break

letters = 0
words = len(user_input.split())  # Counts the words in a sentence by spaces
sentences = 0

for letter in user_input:  # Finds the number of letters excluding special characters
    if letter != "." and letter != "!" and letter != "?" and letter != " ":
        letters += 1

for letter in user_input:  # Finds the number of sentences by using special characters
    if letter == "." or letter == "!" or letter == "?":
        sentences += 1

l = round(letters / words * 100)  # Finds average number of letters per 100 words
s = round(sentences / words * 100)  # Finds average number of sentences per 100 words

grade = int(0.0588 * l - 0.296 * s - 15.8)  # Coleman-Liau index

if grade < 1:
    print("Before Grade 1")

elif grade >= 16:
    print("Grade 16+")

else:
    print("Grade", grade)

print(l, s, grade)