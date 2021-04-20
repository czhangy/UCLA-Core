#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	// Num args error
	if (argc == 1)
	{
		perror("No command line arguments found\n");
		exit(EINVAL);
	}
	// Initialize variables + pipe
	int i, pid, status, input = 0;
	for (i = 1; i < argc; i++)
	{
		int fds[2]; // [0] = read, [1] = write
		status = pipe(fds);
		// Pipe error
		if (status == -1)
		{
			status = errno;
			perror("Pipe failed\n");
			exit(status);
		}
		pid = fork();
		// Child process
		if (pid == 0)
		{
			status = dup2(input, STDIN_FILENO);
			// dup2 error
			if (status == -1)
			{
				status = errno;
				perror("Failed to link to previous pipe\n");
				exit(status);
			}
			if (i < argc - 1)
			{
				status = dup2(fds[1], STDOUT_FILENO);
				// dup2 error
				if (status == -1)
				{
					status = errno;
					perror("Failed to link to write end of pipe\n");
					exit(status);
				}
			}
			status = close(fds[0]);
			if (status == -1)
			{
				status = errno;
				perror("Failed to close\n");
				exit(status);
			}
			status = close(fds[1]);
			if (status == -1)
			{
				status = errno;
				perror("Failed to close\n");
				exit(status);
			}
			status = execlp(argv[i], argv[i], NULL);
			// execlp error
			if (status == -1)
			{
				status = errno;
				perror("execlp failed\n");
				exit(status);
			}
		}
		// Parent process
		else if (pid > 0)
		{
			status = 0;
			waitpid(pid, &status, 0);
			close(fds[1]);
			if (status == -1)
			{
				status = errno;
				perror("Failed to close\n");
				exit(status);
			}
			input = fds[0];
		}
		// Fork error
		else
		{
			status = errno;
			perror("Fork failed\n");
			exit(status);
		}
	}
	return 0;
}

/* ------------------------------------------------------------------------------------
Simple pipe: the child takes the first arg by closing stdout/the read end, then pipes it
to the parent, which takes the second arg by closing stdin/the write end
------------------------------------------------------------------------------------ */

// int fds[2]; // [0] is read end, [1] is write end
// pipe(fds);
// int ret = fork();
// // Child process
// if (ret == 0)
// {
// 	close(STDOUT_FILENO);
// 	// Child isn't going to use the read pipe
// 	close(fds[0]);
// 	// dup the write end of the pipe as stdout
// 	dup(fds[1]);
// 	// Become the first process
// 	execlp(argv[1], argv[1], NULL);
// 	// Close on error
// 	close(fds[1]);
// }
// // Parent process
// else if (ret > 0)
// {
// 	close(STDIN_FILENO);
// 	// Parent isn't going to use the write pipe
// 	close(fds[1]);
// 	// dup the read end of the pipe as stdin
// 	dup(fds[0]);
// 	// Become the second process
// 	execlp(argv[2], argv[2], NULL);
// 	// Close on error
// 	close(fds[0]);
// }
// return 0;
