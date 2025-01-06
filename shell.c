#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

int main(void)
{
	char *command = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	char *args[2];

	while (1)
	{
		printf("#cisfun$ ");
		fflush(stdout);

		nread = getline(&command, &len, stdin);
		if (nread == -1) 
		{
			printf("\n");
			free(command);
			exit(0);
		}

		command[nread - 1] = '\0';

		
		args[0] = command;
		args[1] = NULL;

		pid = fork();
		if (pid == 0) 
		{
			if (execve(command ,args, environ) == -1)
			{
				perror("./shell");
				exit(1);
			}
		}
		else if (pid < 0)
		{
			perror("fork");
			free(command);
			exit(1);
		}
		else
		{
			wait(NULL);
		}
	}
	
	return 0;
}
