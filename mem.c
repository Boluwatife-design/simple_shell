#include "shell.h"

/**
 * ffree-frees a pointer and NULLs the address
 * @ptr: pointer address
 * Return: 1 if free,else 0
 */
int ffree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
