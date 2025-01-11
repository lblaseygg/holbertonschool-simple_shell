#include "main.h"

/**
 * main - Entry point of the shell program
 * @argc: Argument count
 * @argv: Argument vector
 * Return: Always 0 on success
 */
int main(int argc, char **argv)
{
	char *input = NULL;
	size_t len = 0;
	ssize_t read_status;
	char **args;
	int interactive, command_count = 0;

	(void)argc;
	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			printf("#cisfun$ ");
		read_status = getline(&input, &len, stdin);
		if (read_status == -1)
		{
			if (interactive)
				printf("\n");
			free(input);
			break;
		}
		if (input[read_status - 1] == '\n')
			input[read_status - 1] = '\0';

		command_count++;

		args = parse_input(input);
		if (args == NULL || args[0] == NULL)
		{
			free(args);
			continue;
		}

		if (builtins(args, input))
		{
			free(args);
			continue;
		}

		if (commands(args, argv[0], command_count) == -1)
			fprintf(stderr, "%s: %d: %s: not found\n", argv[0], command_count, args[0]);

		free(args);
	}
	return (0);
}
