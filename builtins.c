#include "main.h"

/**
 * parse_input - Tokenizes the user input into arguments
 *
 * @input: User input string
 *
 * Return: Array of arguments, or NULL on failure
 */
char **parse_input(char *input)
{
	char **args;
	char *token;
	int i;

	args = malloc(MAX_ARGS * sizeof(char *));
	if (!args)
	{
		perror("malloc");
		return (NULL);
	}

	token = strtok(input, " ");
	i = 0;
	while (token != NULL && i < MAX_ARGS - 1)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	return (args);
}

/**
 * builtins - Handles built-in commands like 'exit' and 'env'
 *
 * @args: Array of arguments
 * @input: User input string
 *
 * Return: 1 if a built-in was handled, 0 otherwise
 */
int builtins(char **args, char *input)
{
	if (strcmp(args[0], "exit") == 0)
	{
		free(input);
		exit(0);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		char **env = environ;

		while (*env)
			printf("%s\n", *env++);
		return (1);
	}
	return (0);
}
