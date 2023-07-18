#include "shell.h"

/**
 * get_env - returns the string array of our environment
 * @info: Structure containing potential arguments.
 * Return: 0
 */
char **get_env(info_t *info)
{
	if (!info->env || info->en_changed)
	{
		info->env = list_to_strings(info->en);
		info->en_changed = 0;
	}

	return (info->env);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments
 * @var: the string env variable
 * Return: 1 on delete, else 0
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->en;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->en_changed = delete_node_at_index(&(info->en), i);
			i = 0;
			node = info->en;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->en_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments.
 * @var: the string env var property
 * @value: represent value
 *  Return: 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->en;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->en_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->en), buf, 0);
	free(buf);
	info->en_changed = 1;
	return (0);
}
