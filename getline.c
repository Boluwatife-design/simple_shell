#include "shell.h"

/**
 * insert_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len variable
 * Return: bytes
 */
ssize_t insert_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t s = 0;
	size_t len_p = 0;

	if (!*len)
	{

		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);

		s = getline(buf, &len_p, stdin);

		s = _getline(info, buf, &len_p);

		if (s > 0)
		{
			if ((*buf)[s - 1] == '\n')
			{
				(*buf)[s - 1] = '\0';
				s--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);

			{
				*len = s;
				info->cmd_buf = buf;
			}
		}
	}
	return (s);
}

/**
 * _input - put a line minus the newline
 * @info: parameter struct
 * Return: bytes
 */
ssize_t _input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t s = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	s = input_buf(info, &buf, &len);
	if (s == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (s);
}

/**
 * scan_buf - scans a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: represent size
 * Return: s
 */
ssize_t scan_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t s = 0;

	if (*i)
		return (0);
	s = read(info->readfd, buf, READ_BUF_SIZE);
	if (s >= 0)
		*i = s;
	return (s);
}

/**
 * _putline - put the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: r
 */
int _putline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t s = 0, r = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		r = *length;
	if (i == len)
		i = len = 0;

	s = read_buf(info, buf, &len);
	if (s == -1 || (s == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, r, r ? r + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (r)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	r += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = r;
	*ptr = p;
	return (r);
}

/**
 * sigint - blocks ctrl-C
 * @signal_num: signal number
 * Return: nothing
 */
void sigint(__attribute__((unused))int signal_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
