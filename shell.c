#include "main.h"

int main(void)
{
	char *line = NULL;
	ssize_t nread;
	char **args;

	while (1)
	{
		write(1, "$ ", 2);

		nread = _getline(&line);
		if (nread == -1)
		{
			perror("getline");
			free(line);
			exit(1);
		}
		
		args = tokenize(line);

		if (args[0] != NULL && execute_builtins(args) == 0)
		{
			execute_command(args);
		}

		free(args);
	}
	free(line);
	return (0);
}
