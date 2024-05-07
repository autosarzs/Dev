import argparse
import sys
import requests

def main(repo_repository, issue_number, github_token):
    try:

        # GitHub API endpoint
        url = f"https://api.github.com/repos/{repo_repository}/issues/{issue_number}/timeline"

        # Headers for authentication
        headers = {
            "Authorization": f"Bearer {github_token}",
            "Accept": "application/vnd.github.mockingbird-preview+json"
        }

        # Send GET request to GitHub API
        response = requests.get(url, headers=headers)
        response.raise_for_status()

        # Extract timeline data from response
        timeline = response.json()

        # Count the number of "assigned" events
        assigned_count = sum(1 for event in timeline if event.get('event') == 'assigned')

        # Determine if it's the first assignment
        is_first_assignment = assigned_count == 1

        # Output the result
        print(f"is_first_assignment={is_first_assignment}")
    except requests.exceptions.RequestException as e:
        # Print error to stderr
        print(f"Error occurred while fetching issue timeline: {url} {headers} {repo_repository} {issue_number} {github_token} {e}", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    # Parse command-line arguments
    parser = argparse.ArgumentParser()
    parser.add_argument("--repo", help="Repository name", required=True)
    parser.add_argument("--issue", help="Issue number", required=True)
    parser.add_argument("--token", help="GitHub token", required=True)
    args = parser.parse_args()

    # Call main function with parsed arguments
    main(args.repo, args.issue, args.token)
