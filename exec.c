#include "shell.h"

/**
 * is_cmd-checks if file is executable
 * @info: the info struct
 * @path: file path
 * Return: 1 if true,else 0
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * cp_chars-copy characters
 * @pthstr: PATH string
 * @begin: begin index
 * @stop: stopping index
 * Return: pointer to new buffer
 */
char *cp_chars(char *pthstr, int begin, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = begin; i < stop; i++)
		if (pthstr[i] != ':')
			buf[k++] = pthstr[i];
	buf[k] = 0;
	return (buf);
}
/**
 * get_path-get cmd in the PATH string
 * @info: the info struct
 * @pthstr: the PATH string
 * @cmd: the cmd to find
 * Return: full path of cmd if found or NULL
 */
char *get_path(info_t *info, char *pthstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pthstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pthstr[i] || pthstr[i] == ':')
		{
			path = cp_chars(pthstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pthstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
