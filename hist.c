#include "shell.h"

/**
 * _fetchhistory-fetch history file
 * @info: parameter struct
 * Return: allocated string that contains file hist
 */
char *_fetchhistory(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * _wrthist-creates a file/appends to existing file
 * @info: the parameter struct
 * Return: 1 on success, else -1
 */
int _wrthist(info_t *info)
{
	ssize_t fd;
	char *filename = _fetchhistory(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_setsfd(node->str, fd);
		_setfd('\n', fd);
	}
	_setfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * _RDhist-reads history
 * @info: the parameter struct
 * Return: count on success,else 0
 */
int _RDhist(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = _fetchhistory(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_hist(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_hist(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		_delnode(&(info->history), 0);
	reorder_hist(info);
	return (info->histcount);
}

/**
 * build_hist-adds entry to a history list
 * @info: Structure containing potential arguments.
 * @linecount: the history linecount
 * @buf: represent buffer
 * Return: Always 0
 */
int build_hist(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	_putnodeend(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * reorder_hist-reorders history linked list after change
 * @info: Structure containing potential arguments.
 * Return: the new histcount
 */
int reorder_hist(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
