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


extern char **environ; //added to declare environ

char *find_command_in_path(const char *command)
{
	char *path_env = getenv("PATH");
	char *path_dirs = strdup(path_env); //dup PATH to tokenize it
	char *dir = strtok(path_dirs, ":");
	static char full_path[BUFFER_SIZE];
	struct stat sb;

	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
		if (stat(full_path, &sb) == 0 && (sb.st_mode & S_IXUSR)) //exits command and is executable
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
		printf("#cisfun$ ");
		fflush(stdout);

		//Reads user input
		bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
		if (bytes_read == -1)
		{
			perror("read");
			continue;
		}
		else if (bytes_read == 0) //end of file
		{
			printf("\n");
			break;
		}
		buffer[bytes_read - 1] = '\0'; //removes trailing newline

		if (strcmp(buffer, "exit") == 0)
		{
			break; //to exit the shell
		}

		//skips empty output
		if (strlen(buffer) == 0)
			continue;

		command = buffer;

		//Fork a child process to exec command
		pid_t pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}
		else if (pid == 0) //child process
		{
			//execs command
			char *args[] = {command, NULL};
			if (execve(command, args, environ) == -1)
			{
				perror("./shell");
				exit(EXIT_FAILURE);
			}
		}
		else //parent process
		{
			int status;
			waitpid(pid, &status, 0); //wait for childprocess
		}
	}
}

int main(void)
{
	simple_shell();
	return 0;
}
