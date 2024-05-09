import subprocess
import re
import argparse
import sys

def main(commit_hash):
    try:

        # Initialize variables to track line number and error status
        line_number = 1

        # Get the last commit message
        message = subprocess.check_output(['git', 'show', '--format=%B', '-s', commit_hash]).decode('utf-8')

        # Loop over each line of the commit message
        for line in message.split('\n'):
            # Check first line format
            if line_number == 1:
                if not re.match(r'^\[issue:#[0-9]+\] .{1,100}$', line):
                    print("The first line of the commit message must start with '[issue:#<issue-number>]' followed by a description with a maximum of 100 characters.",file=sys.stderr)
                    sys.exit(1)

            # Check empty line after the first line
            if line_number == 2 and line.strip() != "":
                print("The second line of the commit message must be empty.", file=sys.stderr)

            # Increment line number
            line_number += 1

        # Print result
        print(f"commit with hash {commit_hash} is valid")

    except subprocess.CalledProcessError as e:
        print(f"Error occurred while checking commit message: {e}", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    # Parse command-line arguments
    parser = argparse.ArgumentParser()
    parser.add_argument("--commit_hash", help="Commit Hash", required=True)
    args = parser.parse_args()

    # Call main function with parsed arguments
    main(args.commit_hash)
