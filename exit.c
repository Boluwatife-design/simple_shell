#include "shell.h"

/**
 **_strncpy - copies a string to another
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: copied string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int f, k;
	char *s = dest;

	f = 0;
	while (src[f] != '\0' && f < n - 1)
	{
		dest[f] = src[f];
		f++;
	}
	if (f < n)
	{
		k = f;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (s);
}

/**
 **_strncat - Joins two string together
 *@dest: represent string 1
 *@src: represent string 2
 *@n: number of byte
 *Return: concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int f, k;
	char *s = dest;

	f = 0;
	k = 0;
	while (dest[f] != '\0')
		f++;
	while (src[k] != '\0' && k < n)
	{
		dest[f] = src[k];
		f++;
		k++;
	}
	if (k < n)
		dest[f] = '\0';
	return (s);
}

/**
 **_strrchr - locates a character
 *@s: string to be parsed
 *@c: character to look for
 *Return: (s) a pointer to the memory address
 */
char *_strrchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
