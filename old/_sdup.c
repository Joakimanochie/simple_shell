#include "shell.h"

/**
 * _strdup - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter
 * @str: string to duplicate
 * Return: pointer to duplicated string in allocated memory
 */
char *_strdup(char *str)
{
	char *duplicate_str;
	int j, len = 0;

	if (str == NULL)
		return (NULL);

	while (*(str + len))
		len++;
	len++;

	duplicate_str = malloc(sizeof(char) * len);
	if (duplicate_str == NULL)
		return (NULL);

	j = 0;
	while (j < len)
	{
		*(duplicate_str + j) = *(str + j);
		j++;
	}

	return (duplicate_str);
}
