#include "shell.h"

/**
 * _shellmain-main shell loop
 * @info: the parameter and  return info struct
 * @av: represents argument vector
 * Return: 0 on success,else 1 on error
 */
int _shellmain(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		_eraseinfo(info);
		if (interact(info))
			_sets("$ ");
		_printchar(BUF_FLUSH);
		r = _input(info);
		if (r != -1)
		{
			_putinfo(info, av);
			builtin_ret = _builtin(info);
			if (builtin_ret == -1)
				get_cmd(info);
		}
		else if (interact(info))
			_putchar('\n');
		_free(info, 0);
	}
	_wrthist(info);
	_free(info, 1);
	if (!interact(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}
/**
 * _builtin-finds a builtin command
 * @info: the parameter and return info struct
 * Return: -1 if no builtin,0 if success
 * 1 if builtin found but not success,2 if signals exit
 */
int _builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _shellexit},
		{"env", _env},
		{"help", _dir},
		{"history", _history},
		{"setenv", _nsetenv},
		{"unsetenv", _nunsetenv},
		{"cd", _cd},
		{"alias", _alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * get_cmd-gets a command in PATH
 * @info: the parameter and return info struct
 * Return: void
 */
void get_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = get_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interact(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			_error(info, "not valid\n");
		}
	}
}

/**
 * fork_cmd-split an exec thread to run cmd
 * @info: the parameter and return info struct
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, _getenviron(info)) == -1)
		{
			_free(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}

	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				_error(info, "access denied\n");
		}
	}
}
