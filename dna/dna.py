import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Command: python ./dna.py <database.csv> <sequence.txt>")
        exit()

    # TODO: Read database file into a variable
    db = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            db.append(row)

    # TODO: Read DNA sequence file into a variable
    dna_seq = ""
    with open(sys.argv[2]) as file:
        dna_seq = file.read().strip()  # .strip() from https://www.geeksforgeeks.org/python-removing-newline-character-from-string/

    # TODO: Find longest match of each STR in DNA sequence
    seq_num = {}
    for subseq in db[0].keys():
        if subseq == "name":
            continue
        seq_num[subseq] = longest_match(dna_seq, subseq)

    # TODO: Check database for matching profiles
    match = {}
    count = 1

    for profile in db:
        count = 1
        for subseq in seq_num:
            if subseq in profile:
                if int(profile[subseq]) == int(seq_num[subseq]):
                    match[profile['name']] = count
                    count += 1

    for key, value in match.items():
        if value == len(seq_num):
            print(key)
            return

    print("No match.")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
