#include "main.h"

/**
 * _getenv - Retrieves the value of an environment variable
 * @name: Environment variable name
 * Return: The value of the variable, or null if not found
 */
char *_getenv(const char *name)
{
	extern char **environ;
	char *var;
	size_t len;

	len = _strlen(name);
	while (*environ)
	{
		var = *environ;
		if (_strncmp(var, name, len) == 0 && var[len] == '=')
		{
			return (var + len + 1);
		}
		environ++;
	}
	return (NULL);
}
