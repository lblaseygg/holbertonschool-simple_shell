#include "main.h"

/**
 * commands - Searches for a command in the PATH and executes it
 *
 * @args: Array of arguments, with args[0] as the command
 * @program_name: Name of the shell program
 * @command_count: Command number for error messages
 *
 * Return: 0 on success, -1 if the command was not found
 */
int commands(char **args, char *program_name, int command_count)
{
	char *path, *path_copy, *dir, *command_path;
	size_t cmd_len, dir_len;

	path = _getnev("PATH");
	if (!path || strchr(args[0], '/'))
		return (access(args[0], X_OK) == 0 ? executable(args) : -1);

	path_copy = strdup(path);
	if (!path_copy)
	{
		perror("strdup");
		return (-1);
	}

	dir = strtok(path_copy, ":");
	cmd_len = strlen(args[0]);
	while (dir)
	{
		dir_len = strlen(dir);
		command_path = malloc(dir_len + cmd_len + 2);
		if (!command_path)
		{
			perror("malloc");
			free(path_copy);
			return (-1);
		}
		sprintf(command_path, "%s/%s", dir, args[0]);
		if (access(command_path, X_OK) == 0)
		{
			free(path_copy);
			args[0] = command_path;
			return (executable(args));
		}
		free(command_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	fprintf(stderr, "%s: %d: %s: not found\n",
			program_name, command_count, args[0]);
	return (-1);
}
