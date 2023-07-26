#include "shell.h"

/**
 * get_line - stores into malloced buffer the user's command into shell
 * @str: buffer
 * Return: number of characters read
 */
size_t get_line(char **str)
{
	ssize_t j = 0, size = 0, t1 = 0, t2 = 0, n = 0;
	char buff[1024];

	while (t2 == 0 && (j = read(STDIN_FILENO, buff, 1024 - 1)))
	{
		if (j == -1)
			return (-1);

		buff[j] = '\0';

		n = 0; 
		while (buff[n] != '\0')
		{
			if (buff[n] == '\n')
		                t2 = 1;
		        n++;
		}
		if (t1 == 0)
		{
			j++;
			*str = malloc(sizeof(char) * j);
			*str = _strcpy(*str, buff);
			size = j;
			t1 = 1;
		}
		else 
		{
			size += j;
			*str = _strcat(*str, buff);
		}
	}
	return (size);
}
