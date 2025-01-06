#include "main.h"

/**
 * execute_builtins - Executes built-in shell commands.
 * @args: Array of arguments
 * Return: ! if a built-in command was executed, 0 otherwise
 */
int execute_builtins(char **args)
{
	if (_strcmp(args[0], "exit") == 0)
	{
		exit(0);
	}
	else if (_strcmp(args[0], "env") == 0)
	{
		print_env();
		return (1);
	}
	return (0);
}

/**
 * print_env - Prints all the environment variables
 * Return: 0 on success
 */
int print_env(void)
{
	extern char **environ;
	int i = 0;

	while (environ[i])
	{
		write(1, environ[i], _strlen(environ[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
