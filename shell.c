#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdbool.h>

#define BUFFER_SIZE 1042

extern char **environ; // Added to declare environ

char *find_command_in_path(const char *command)
{
	char *path_env = getenv("PATH");
	char *path_dirs = strdup(path_env); // Duplicate PATH to tokenize it
	char *dir = strtok(path_dirs, ":");
	static char full_path[BUFFER_SIZE];
	struct stat sb;

	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
		if (stat(full_path, &sb) == 0 && (sb.st_mode & S_IXUSR)) // Exists and is executable
 		{
			free(path_dirs);
			return full_path;
		}
		dir = strtok(NULL, ":");
	}

	free(path_dirs);
	return NULL;
}

void simple_shell()
{
	char buffer[BUFFER_SIZE];
	char *command;
	ssize_t bytes_read;

	while (true)
	{
		printf(":) ");
		fflush(stdout);

	// Read user input
	bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
	if (bytes_read == -1)
	{
		perror("read");
		continue;
	}
		else if (bytes_read == 0) // End of file
	{
		printf("\n");
		break;
	}
	buffer[bytes_read - 1] = '\0'; // Remove trailing newline

	if (strcmp(buffer, "exit") == 0)
	{
		break; // Exit the shell
	}

	// Skip empty output
	if (strlen(buffer) == 0)
		continue;

	command = find_command_in_path(buffer);
	if (command == NULL)
	{
		printf("Command not found: %s\n", buffer);
		continue; //skip to the next iteration if command doesn't exist
	}

	// Fork a child process to exec command
	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork");
		continue;
	}
	else if (pid == 0) // Child process
	{
		char *args[] = {command, NULL};
		if (execve(command, args, environ) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else // Parent process
		{
		int status;
		waitpid(pid, &status, 0); // Wait for child process
		}
	}
}

int main(void)
{
 	simple_shell();
	return 0;
}
