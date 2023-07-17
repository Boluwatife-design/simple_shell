#include "shell.h"

/**
 * _history - displays history list, one command by line,starting at 0.
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int _history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * undo_alias - undo alias
 * @info: parameter structure
 * @str: the string
 * Return: Always 0 on success, else 1
 */
int undo_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchar(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * put_alias - assign alias to string
 * @info: parameter structure
 * @str: the string
 * Return: Always 0 on success, else 1
 */
int put_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (undo_alias(info, str));

	undo_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * list_alias - prints an alias string
 * @node: the alias node
 * Return: Always 0 on success, else 1
 */
int list_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int _alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			list_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			put_alias(info, info->argv[i]);
		else
			list_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
