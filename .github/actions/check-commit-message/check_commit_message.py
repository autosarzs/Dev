import requests
import re
import argparse
import sys

def main(commits_url, token):
    try:
        # Fetch commits from the pull request
        headers = {"Authorization": f"token {token}"}
        response = requests.get(commits_url + "?per_page=100", headers=headers)
        response.raise_for_status()
        commits = response.json()

        # Get the last commit message
        last_message = commits[-1]['commit']['message']

        # Loop over each line of the commit message
        line_number = 1
        for line in last_message.split('\n'):
            # Check first line format
            if line_number == 1:
                if not re.match(r'^\[issue:#[0-9]+\] .{1,100}$', line):
                    print("The first line of the commit message must start with '[issue:#<issue-number>]' followed by a description with a maximum of 100 characters.", file=sys.stderr)
                    sys.exit(1)

            # Check empty line after the first line
            if line_number == 2 and line.strip() != "":
                print("The second line of the commit message must be empty.", file=sys.stderr)
                sys.exit(1)

            # Increment line number
            line_number += 1

        # Print result
        print(f"Commit with hash {commits[-1]['sha']} is valid")

    except Exception as e:
        print(f"Error occurred while checking commit message: {e}", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    # Parse command-line arguments
    parser = argparse.ArgumentParser()
    parser.add_argument("--commits_url", help="Pull Request Commits Url", required=True)
    parser.add_argument("--token", help="GitHub Token", required=True)
    args = parser.parse_args()

    # Call main function with parsed arguments
    main(args.commits_url, args.token)
