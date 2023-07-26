#include "shell.h"

/**
 * _strtoint-convert a string to an integer
 * @s: the string to convert
 * Return: 0 if no numbers in string,else -1
 */
int _strtoint(char *s)
{
	int i = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			res *= 10;
			res += (s[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * _error - prints an error message
 * @info: the parameter and return info struct
 * @errstr: string containing specified error type
 * Return: 0 if no numbers in string,else -1
 */
void _error(info_t *info, char *errstr)
{
	_print(info->fname);
	_print(": ");
	_decimal(info->line_count, STDERR_FILENO);
	_print(": ");
	_print(info->argv[0]);
	_print(": ");
	_print(errstr);
}

/**
 * _decimal-function that prints a decimal number
 * @input: the input
 * @fd: the filedescriptor to write to
 * Return: number of characters printed
 */
int _decimal(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _printchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * _converter-converter function
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */
char *_converter(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * _rmcomment-function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 * Return: Always 0
 */
void _rmcomment(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
