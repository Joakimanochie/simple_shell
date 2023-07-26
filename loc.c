#include "shell.h"

/**
 * _realloc - allocate memory and set all values to 0
 * @pt: pointer to the memory previously allocated (malloc(o_size))
 * @o_size: size previously allocated
 * @n_size: new size to reallocate
 * Return: pointer to reallocated memory
 */

void *_realloc(void *pt, unsigned int o_size, unsigned int n_size)
{
	void *q;
	unsigned int i;

	if (n_size == 0 && pt != NULL)
	{
		free(pt);
		return (NULL);
	}

	if (n_size == o_size)
		return (pt);

	if (pt == NULL)
	{
		q = malloc(n_size);
		if (q == NULL)
			return (NULL);
		else
			return (q);
	}

	q = malloc(n_size);
	if (q == NULL)
		return (NULL);

	for (i = 0; i < o_size && i < n_size; i++)
		*((char *)q + i) = *((char *)pt + i);
	free(pt);

	return (q);
}
