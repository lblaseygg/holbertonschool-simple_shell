#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>
#include <errno.h>

#define MAX_ARGS 10

char **parse_input(char *input);
int executable(char **args);
int builtins(char **args, char *input);
char *_getnev(const char *name);
int commands(char **args, char *program_name, int command_count);

extern char **environ;

#endif /* SHELL_H */
