#include "shell.h"

/**
 * free_double_ptr - free malloced arrays
 * @str: array of strings
 */
void free_double_ptr(char **str)
{
	int j = 0;

	while (str[j] != NULL)
	{
		free(str[j]);
		j++;
	}
	free(str);
}

