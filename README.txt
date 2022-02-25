How to Run:
1. Navigate to project folder
2. Run "make"
3. Ensure that file "cstest" is empty for best results
4. Invoke program using "./master # [-t #]"
    - The first '#' is the number of processes you want to run. It will default to 2
if not given. Minimum 1, max 20.
    - The second '#', preceded by '-t' is the maximum amount of time you want the
program to run for. It will default to 100 if not given.

Git Repository: https://github.com/Netsaken/UMSL-CS-4760-Project-2

Problems:
- All outputs to cstest print with the same Queue number, 1. Not sure that's correct.
- The times logged to logfile for exit is too close to the time logged for entering.
- When the program is killed by ctrl-C or time-out, everything is shut down immediately
without giving child processes time to exit gracefully.
- Related to the above, there is no code for multiple ctrl-c signals.
- There seem to be two processes being created that are not being deleted.

- Had a major issue trying to concatenate argv[0] to the end of a string for the logfile
names, causing the project to be submitted late. Only using strcat on an array[] worked.