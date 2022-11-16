import csv
import sys
import json


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable --> databases/large.csv
    database = []

    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            database.append(row)

    # debug with pretty print
    # print(json.dumps(database, indent=2))

    # TODO: Read DNA sequence file into a variable --> sequences/5.txt (for example)
    with open(sys.argv[2], "r") as file:
        sequence = file.readlines()

    # debug
    # print(sequence)

    # TODO: Find longest match of each STR in DNA sequence
    # get list of STRs from database keys
    STRs = list(database[0].keys())
    # remove 'name' key
    STRs.remove("name")

    # initialize dictionary of longest_sequences
    longest_sequences = {key: 0 for key in STRs}

    for str in STRs:
        # debug
        # print("subsequence: ", str)
        # print("subsequence_length: ", len(str))
        # print("sequence: ", sequence)
        # print("sequence_length: ", len(sequence))
        data = longest_match(sequence=sequence[0], subsequence=str)
        longest_sequences[str] = data

    # TODO: Check database for matching profiles

    in_database = False
    # in_database_name = Null

    for persona in database:
        counter = 0  # counter to ensure we check for all SRSs
        for STR in STRs:  # check all STRs
            if int(persona[STR]) == longest_sequences[STR]:
                counter += 1
        if counter == len(STRs):
            print(persona['name'])
            in_database = True  # person found

    if not in_database:
        print("No match")

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
