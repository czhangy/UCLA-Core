#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	// Num args error handling
	if (argc == 1)
	{
		perror("No command line arguments found\n");
		exit(EINVAL);
	}
	// Init vars
	int i, pid = 1, argnum, status;
	// Init pid container
	int pids[argc - 1];
	// Init pipes container
	int pipes[2 * (argc - 2)];
	// Init pipes
	for (int i = 0; i < 2 * (argc - 2); i += 2)
	{
		status = pipe(pipes + i);
		// pipe error handling
		if (status == -1)
		{
			status = errno;
			perror("Pipe failed\n");
			exit(status);
		}
	}
	// Create all children
	for (i = 1; i < argc; i++)
	{
		pid = fork();
		// Save pid for cleanup later
		pids[i - 1] = pid;
		// Save argnum for indexing
		argnum = i;
		// fork error handling
		if (pid < 0)
		{
			status = errno;
			perror("Fork failed\n");
			exit(status);
		}
		// If child, stop forking
		else if (pid == 0)
			break;
	}
	// Child processes
	if (pid == 0)
	{
		// Connect read end of last pipe to fd = 0 of current process
		if (argnum != 1)
		{
			status = dup2(pipes[2 * (argnum - 2)], STDIN_FILENO);
			// dup2 error handling
			if (status == -1)
			{
				status = errno;
				perror("Failed to link to previous pipe\n");
				exit(status);
			}
		}
		// Connect write end of current pipe to fd = 1 of current process
		if (argnum != argc - 1)
		{
			status = dup2(pipes[2 * argnum - 1], STDOUT_FILENO);
			// dup2 error handling
			if (status == -1)
			{
				status = errno;
				perror("Failed to link to previous pipe\n");
				exit(status);
			}
		}
		// Close file descriptors
		for (i = 0; i < 2 * (argc - 2); i++)
			close(pipes[i]);
		// Use execlp to change processes
		status = execlp(argv[argnum], argv[argnum], NULL);
		// execlp error handling
		if (status == -1)
		{
			status = errno;
			perror("execlp failed\n");
			exit(status);
		}
	}
	// Parent process
	else
	{
		// Close file descriptors
		for (i = 0; i < 2 * (argc - 2); i++)
			close(pipes[i]);
		for (i = 0; i < argc - 1; i++)
		{
			// Wait for child processes
			if (waitpid(pids[i], &status, 0) == -1)
			{
				status = errno;
				perror("waitpid failed\n");
				exit(errno);
			}
			// Check for error codes from children
			if (WIFEXITED(status))
				if (WEXITSTATUS(status) != 0)
					exit(WEXITSTATUS(status));
		}
	}
	return 0;
}
