#include "main.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define READ_BUF_SIZE 1024

/**
 * _getline - Reads input from stdin
 * @line: Pointer to the buffer for input
 * Return: the number of bytes read, or -1 on failure
 */
ssize_t _getline(char **line)
{
	static char buffer[READ_BUF_SIZE];
	static size_t buf_pos = 0, buf_size = 0;
	size_t len = 0;
	char *new_line = NULL;
	char c = '\0';

	if (!line)
		return (-1);

	*line = malloc(READ_BUF_SIZE);
	if (!*line)
		return (-1);

	while (1)
	{
		if (buf_pos == buf_size)
		{
			buf_size = read(STDIN_FILENO, buffer, READ_BUF_SIZE);
			buf_pos = 0;
			if (buf_size == 0)
				return (len > 0 ? (ssize_t)len : -1);
			if (buf_size == (size_t)-1)
			{
				free(*line);
				return(-1);
			}
		}

		c = buffer[buf_pos++];
		if (c == '\n')
		{
			(*line)[len] = '\0';
			return (ssize_t)(len + 1);
		}

		(*line)[len++] = c;

		if (len % READ_BUF_SIZE == 0)
		{
			new_line = realloc(*line, len + READ_BUF_SIZE);
			if (!new_line)
			{
				free(*line);
				return (-1);
			}
			*line = new_line;
		}
	}
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
		if (!args)
		{
			perror("realloc");
			free(args);
			return (NULL);
		}
		args[i++] = token;
		token = strtok(NULL, " \t\n");
	}

	args = realloc(args, sizeof(char *) * (i + 1));
	if (!args)
	{
		perror("realloc");
		free(args);
		return(NULL);
	}
	args[i] = NULL;
	
	return args;
}
