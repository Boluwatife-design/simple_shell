#include "shell.h"

/**
 * _env - prints current environment
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _env(info_t *info)
{
	_printstr(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments.
 * @name: var name
 * Return: value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = begin_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _nsetenv - create a new environ var
 * @info: Structure containing potential arguments.
 *  Return: 0
 */
int _nsetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_print("Invalid number of argument\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _nunsetenv - Remove an environ variable
 * @info: Structure containing potential arguments
 * Return: 0
 */
int _nunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_print("argument is too little\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * add_env_list - add environment list
 * @info: Structure containing potential arguments.
 * Return: 0
 */
int add_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		_putnodeend(&node, environ[i], 0);
	info->env = node;
	return (0);
}
