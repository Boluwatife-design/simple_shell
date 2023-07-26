#include "shell.h"

/**
 * _eraseinfo-initializes info_t struct
 * @info: struct address
 */
void _eraseinfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * _putinfo - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void _putinfo(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = splitstr(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		change_alias(info);
		change_vars(info);
	}
}

/**
 * _free-frees info_t
 * @info: struct address
 * @all: true if freeing all fields
 */
void _free(info_t *info, int all)
{
	frees(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			_freelist(&(info->env));
		if (info->history)
			_freelist(&(info->history));
		if (info->alias)
			_freelist(&(info->alias));
		frees(info->environ);
			info->environ = NULL;
		ffree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
