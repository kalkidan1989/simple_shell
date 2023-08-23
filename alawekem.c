#include "shell.h"

/**
 * cmd_niew - determines if a file is an executable command
 * @path: path to the file
 * @mereja: the mereja struct
 * Return: 1 if true, 0 otherwise
 */
int cmd_niew(mereja_t *mereja, char *path)
{
	struct stat st;

	(void)mereja;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * fiidel_mabizate - duplicates characters
 * @pathstr: the PATH string
 * @stop: stopping index
 * @start: starting index
 * Return: pointer to new buffer
 */
char *fiidel_mabizate(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @cmd: the cmd to find
 * @mereja: the mereja struct
 * @pathstr: the PATH string
 * Return: full path of cmd if found or NULL
 */
char *find_path(mereja_t *mereja, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (cmd_niew(mereja, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = fiidel_mabizate(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (cmd_niew(mereja, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
