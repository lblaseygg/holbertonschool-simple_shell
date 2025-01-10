#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024 /* Maximum characters the user can type in one line */
#define MAX_ARGS 100 /* Maximum number of arguments a single command can have */

int main(void)
{
	char *line = NULL; /* Pointer for the user input */
	size_t len = 0; /* Size of the buffer */
	ssize_t nread; /* Number of characters read */

	while (1)
	{
		printf("#cisfun$ ");
		fflush(stdout);
