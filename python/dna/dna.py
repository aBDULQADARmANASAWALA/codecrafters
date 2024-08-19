import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Error")
        return

    # TODO: Read database file into a variable
    with open(sys.argv[1]) as file:
        csv_reader = csv.DictR  eader(file)

        rows = []
        str_count = len(csv_reader.fieldnames) - 1
        for row in csv_reader:
            rows.append(row)
        print(rows)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as dna:
        dna_reader = dna.read()

    # TODO: Find longest match of each STR in DNA sequence
    data = []
    for ele in csv_reader.fieldnames:
        next if ele == "name" else data.append(
            {"str": ele, "count": longest_match(dna_reader, ele)})

    # TODO: Check database for matching profiles
    count = 0
    for i in rows:
        for j in data:
            if j["count"] == int(i[j["str"]]):
                count += 1
            else:
                count = 0
                break
        if count == str_count:
            print(i["name"])
            return
    else:
        print("No Match")


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
