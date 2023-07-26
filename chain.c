#include "shell.h"

/**
 * checks_chain-checks if current char is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * Return: 1 if chain delimeter,else 0
 */
int checks_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * scan_chain-scan if to continue chaining
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 * Return: Void
 */
void scan_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * change_alias-change an aliases in the tokenized string
 * @info: the parameter struct
 * Return: 1 if replaced,else 0
 */
int change_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = begin_node(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strrchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * change_vars-change vars in the tokenized string
 * @info: the parameter struct
 * Return: 1 if replaced,else 0
 */
int change_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			change_string(&(info->argv[i]),
					_strdup(_converter(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			change_string(&(info->argv[i]),
					_strdup(_converter(getpid(), 10, 0)));
			continue;
		}
		node = begin_node(info->env, &info->argv[i][1], '=');
		if (node)
		{
			change_string(&(info->argv[i]),
					_strdup(_strrchr(node->str, '=') + 1));
			continue;
		}
		change_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * change_string-change string
 * @old: address of old string
 * @new: new string
 * Return: 1 if replaced,else 0
 */
int change_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
