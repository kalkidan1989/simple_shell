#include "shell.h"

/**
 * yeneexit - exits the shell
 * @mereja: Structure containing potential arguments.
 * Return: exits with a given exit status
 */
int yeneexit(mereja_t *mereja)
{
	int tekotatari;

	if (mereja->argv[1]) /* If there is an exit arguement */
	{
		tekotatari = sehetetrratoi(mereja->argv[1]);
		if (tekotatari == -1)
		{
			mereja->status = 2;
			printsehetetrror(mereja, "Illegal number: ");
			sehetetputs(mereja->argv[1]);
			sehetetputchar('\n');
			return (1);
		}
		mereja->err_num = sehetetrratoi(mereja->argv[1]);
		return (-2);
	}
	mereja->err_num = -1;
	return (-2);
}

/**
 * mahider_mekeyer - changes the current directory of the process
 * @mereja: Structure containing potential arguments.
 * Return: Always 0
 */
int mahider_mekeyer(mereja_t *mereja)
{
	char *s, *dir, buffer[1024];
	int yetekeyeru_melse;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!mereja->argv[1])
	{
		dir = _getenv(mereja, "HOME=");
		if (!dir)
			yetekeyeru_melse = chdir((dir = _getenv(mereja, "PWD=")) ? dir : "/");
		else
			yetekeyeru_melse = chdir(dir);
	}
	else if (_strcmp(mereja->argv[1], "-") == 0)
	{
		if (!_getenv(mereja, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(mereja, "OLDPWD=")), _putchar('\n');
		yetekeyeru_melse = chdir((dir = _getenv(mereja, "OLDPWD=")) ? dir : "/");
	}
	else
		yetekeyeru_melse = chdir(mereja->argv[1]);
	if (yetekeyeru_melse == -1)
	{
		printsehetetrror(mereja, "can't cd to ");
		sehetetputs(mereja->argv[1]), sehetetputchar('\n');
	}
	else
	{
		_makenv(mereja, "OLDPWD", _getenv(mereja, "PWD="));
		_makenv(mereja, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * yenesehetetrdata - changes the current directory of the process
 * @mereja: Structure containing potential arguments.
 * Return: Always 0
 */
int yenesehetetrdata(mereja_t *mereja)
{
	char **arg_array;

	arg_array = mereja->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
