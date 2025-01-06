#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>


#define BUFFER_SIZE 1024

ssize_t _getline(char **line);
char **tokenize(char *line);
int execute_command(char **args);
int _putchar(char c);
void free_memory(char **array);
int execute_builtins(char **args);
int print_env(void);
int _strcmp(char *s1, char *s2);
int _strlen(const char *s);
int _strncmp(char *s1, const char *s2, size_t n);




#endif
