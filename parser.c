#include "main.h"

/**
 * _getline - Reads input from stdin
 * @line: Pointer to the buffer for input
 * Return: the number of bytes read, or -1 on failure
 */
ssize_t _getline(char **line)
{
	size_t len = 0;
	ssize_t nread;

	nread = getline(line, &len, stdin);
	if (nread == -1)
	{
		return (-1);
	}
	return (nread);
}

/**
 * tokenize - Tokenizes input into an array of arguments
 * @line: Input string
 * Return: Array of argument strings
 */
char **tokenize(char *line)
{
	char **args = NULL;
	char *token = strtok(line, " \t\n");
	int i = 0;

	while (token)
	{
		args = realloc(args, sizeof(char *) * (i + 1));
		args[i] = token;
		i++;
		token = strtok(NULL, " \t\n");
	}
	args = realloc(args, sizeof(char *) * (i + 1));
	args[i] = NULL;

	return args;
}
