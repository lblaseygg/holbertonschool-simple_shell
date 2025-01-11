#include "main.h"

/**
 * executable - Executes a command using execve
 *
 * @args: Array of arguments
 *
 * Return: 0 on success, -1 on failure
 */
int executable(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
	return (0);
}
