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
 * @argv: argument vector
 */
void _putinfo(info_t *info, char **argv)
{
	int i = 0;

	info->fname = argv[0];
	if (info->arg)
	{
		info->av = strtow(info->arg, " \t");
		if (!info->av)
		{
			info->av = malloc(sizeof(char *) * 2);
			if (info->av)
			{
				info->av[0] = _strdup(info->arg);
				info->av[1] = NULL;
			}
		}
		for (i = 0; info->av && info->av[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * _free-frees info_t
 * @info: struct address
 * @all: true if freeing all fields
 */
void _free(info_t *info, int all)
{
	ffree(info->av);
	info->av = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
