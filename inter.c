i#include "shell.h"

/**
 * interact-returns 1 if shell is interactive
 * @info: address
 * Return: 1 if interactive, else 0
 */
int interact(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * _delim-checks if character is delimeter
 * @c: the character to check
 * @del: the delimeter
 * Return: 1 if true, else 0
 */
int _delim(char c, char *del)
{
	while (*del)
		if (*del++ == c)
			return (1);
	return (0);
}

/**
 * _alpha-checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, else 0
 */
int _alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * _toint-converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string.
 */
int _toint(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
