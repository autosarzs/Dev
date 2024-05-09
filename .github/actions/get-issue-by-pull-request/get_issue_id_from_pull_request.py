import argparse
import re
import sys

def extract_issue_id(pull_request_body):
    try:
        # Search for the issue ID using regex
        match = re.search(r'\*\*Issue ID:\*\* #(\d+)', pull_request_body)

        if match:
            issue_id = match.group(1)
            print(f"issue_id={issue_id}")
        else:
            print("Issue ID not found in the pull request body.", file=sys.stderr)
            print("Make sure you are using the pull request template.", file=sys.stderr)

            print(pull_request_body, file=sys.stderr)
            sys.exit(1)

    except Exception as e:
        print(f"Error occurred while extracting issue ID: {e}", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    # Parse command-line arguments
    parser = argparse.ArgumentParser()
    parser.add_argument("--pull_request_body", help="Pull Request Body Message", required=True)
    args = parser.parse_args()

    # Call the function to extract issue ID
    extract_issue_id(args.pull_request_body)
