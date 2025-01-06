#include "main.h"

/**
 * _strcmp - compares two strings.
 * @s1: First string
 * @s2: Second strign
 * Return: 0if strings are equal, negative/positive if different
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 != *s2)
	{
		if (*s1 && *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * _strlen - Returns the length of a string.
 * @s: String
 * Return: Length of string
 */
int _strlen(const char *s)
{
	int len = 0;

	while (s[len])
		len++;
	return (len);
}

/**
 * _strncmp - Compares a specified number of characters
 * @s1: First string
 * @s2: second string
 * @n: Number of characters to compare
 * Return: 0 if equal, negative/positive if different
 */
int _strncmp(char *s1, const char *s2, size_t n)
{
	size_t i = 0;
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (i == n ? 0 : s1[i] - s2[i]);
}

/**
 * free_memory - frees memory allocated to an array
 * @array: array to be freed
 */
void free_memory(char **array)
{
	int i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

