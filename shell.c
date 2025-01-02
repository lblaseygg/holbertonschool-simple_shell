#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1042


extern char **environ; //added to declare environ

typedef enum { false, true } bool;

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
