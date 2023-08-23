#include "shell.h"
/**
* hsh - main shell loop
* @av: the argument vector from main()
* @mereja: the parameter & return mereja struct
* Return: 0 on success, 1 on error, or error code
*/
int hsh(mereja_t *mereja, char **av)
{
ssize_t r = 0;
int yerasu_ret = 0;
while (r != -1 && yerasu_ret != -2)
{
clear_mereja(mereja);
if (interactive_mode(mereja))
_puts("$ ");
sehetetputchar(BUF_FLUSH);
r = get_input(mereja);
if (r != -1)
{
set_mereja(mereja, av);
yerasu_ret = find_yerasu(mereja);
if (yerasu_ret == -1)
find_cmd(mereja);
}
else if (interactive_mode(mereja))
_putchar('\n');
free_mereja(mereja, 0);
}
write_tarik(mereja);
free_mereja(mereja, 1);
if (!interactive_mode(mereja) && mereja->status)
exit(mereja->status);
if (yerasu_ret == -2)
{
if (mereja->err_num == -1)
exit(mereja->status);
exit(mereja->err_num);
}
return (yerasu_ret);
}
/**
* find_yerasu - finds a yerasu command
* @mereja: the parameter & return mereja struct
*
* Return: -1 if yerasu not found,
* 0 if yerasu executed successfully,
* 1 if yerasu found but not successful,
* 2 if yerasu signals exit()
*/
int find_yerasu(mereja_t *mereja)
{
int i, built_in_ret = -1;
yerasu_table yerasutbl[] = {
{"exit", yeneexit},
{"env", yenesehetetnv},
{"help", yenesehetetrdata},
{"tarik", yene_tarike},
{"makenv", yenemakenv},
{"unmakenv", yeneunmakenv},
{"cd", mahider_mekeyer},
{"alias", yene_alias},
{NULL, NULL}
};
for (i = 0; yerasutbl[i].type; i++)
if (_strcmp(mereja->argv[0], yerasutbl[i].type) == 0)
{
mereja->line_count++;
built_in_ret = yerasutbl[i].func(mereja);
break;
}
return (built_in_ret);
}
/**
* find_cmd - finds a command in PATH
* @mereja: the parameter & return mereja struct
*
* Return: void
*/
void find_cmd(mereja_t *mereja)
{
char *path = NULL;
int i, k;
mereja->path = mereja->argv[0];
if (mereja->linecount_flag == 1)
{
mereja->line_count++;
mereja->linecount_flag = 0;
}
for (i = 0, k = 0; mereja->arg[i]; i++)
if (!is_delim(mereja->arg[i], " \t\n"))
k++;
if (!k)
return;
path = find_path(mereja, _getenv(mereja, "PATH="), mereja->argv[0]);
if (path)
{
mereja->path = path;
fork_cmd(mereja);
}
else
{
if ((interactive_mode(mereja) || _getenv(mereja, "PATH=")
|| mereja->argv[0][0] == '/') && cmd_niew(mereja, mereja->argv[0]))
fork_cmd(mereja);
else if (*(mereja->arg) != '\n')
{
mereja->status = 127;
printsehetetrror(mereja, "not found\n");
}
}
}
/**
* fork_cmd - forks a an exec thread to run cmd
* @mereja: the parameter & return mereja struct
*
* Return: void
*/
void fork_cmd(mereja_t *mereja)
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
if (execve(mereja->path, mereja->argv, getsehetetnviron(mereja)) == -1)
{
free_mereja(mereja, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
wait(&(mereja->status));
if (WIFEXITED(mereja->status))
{
mereja->status = WEXITSTATUS(mereja->status);
if (mereja->status == 126)
printsehetetrror(mereja, "Permission denied\n");
}
}
}
