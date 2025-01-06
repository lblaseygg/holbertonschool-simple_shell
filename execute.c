#include "main.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

extern char **environ;

/**
 * resolve_path - resolves the full path of a command
 * @command: The command to resolve
 * Return: the full path to the command, or NULL if not found
 */

char *resolve_path(char *command)
{
	char *path = getenv("PATH");
	char *dir, *full_path;
	struct stat st;

	if (!path)
		return (NULL);

	path = strdup(path);
	if (!path)
		return (NULL);

	dir = strtok(path, ":");
	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		if (!full_path)
		{
			free(path);
			return (NULL);
		}

		sprintf(full_path, "%s/%s", dir, command);

		if (stat(full_path, &st) == 0)
		{
			free(path);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}


/**
 * execute_command - executes a command by forking a new process.
 * @args: Array of arguments
 * Return: 0 on success, 1 on failure
 */
int execute_command(char **args)
{
	pid_t pid;
	char *full_path;

	if (!args[0])
		return (1);

	if (args[0][0] == '/')
	{
		full_path = args[0];
	}
	else
	{
		full_path = resolve_path(args[0]);
	}

	if (!full_path)
	{
		write(STDERR_FILENO, args[0], strlen(args[0]));
		write(STDERR_FILENO, ": command not found\n", 20);
		return (1);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(full_path);
		return (1);
	}

	if (pid == 0)
	{
		if (execve(full_path, args, environ) == -1)
 		{
			perror("execve");
			free(full_path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}

	free(full_path);
	return (0);
}
