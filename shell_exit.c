#include "shell.h"

/**
 * _shellexit - exits the shell
 * @info: Structure containing potential arguments.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int _shellexit(info_t *info)
{
	int checkexit;

	if (info->argv[1])
	{
		checkexit = _strtoint(info->argv[1]);
		if (checkexit == -1)
		{
			info->status = 2;
			_error(info, "Wrong number: ");
			_print(info->argv[1]);
			_printchar('\n');
			return (1);
		}
		info->err_num = _strtoint(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _cd - changes the current directory of the process
 * @info: Structure containin potential arg.
 * Return: Always 0
 */
int _cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, sizeof(buffer));
	if (!s)
		_sets("TODO: >>get cwd failure here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "Home=");
		if (!dir)
			chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
		chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_sets(s);
			_putchar('\n');
			return (1);
		}
		_sets(_getenv(info, "OLDPWD="));
		_putchar('\n');
		chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		_error(info, "can't cd to ");
		_print(info->argv[1]);
		_printchar('\n');
	}
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, sizeof(buffer)));
	}
	return (0);
}

/**
 * _dir - changes the current directory of the process
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _dir(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_sets("command works, yet to apply Function\n");
	if (0)
		_sets(*arg_array);

	return (0);
}
