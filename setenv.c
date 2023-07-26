#include "shell.h"

/**
 * _getenviron - returns the string array of our environment
 * @info: Structure containing potential arguments.
 * Return: 0
 */
char **_getenviron(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = lst_tostr(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments
 * @var: the string env variable
 * Return: 1 on delete, else 0
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = begin_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = _delnode(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
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
	node = info->env;
	while (node)
	{
		p = begin_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	_putnodeend(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
