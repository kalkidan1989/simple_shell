#include "shell.h"
/**
* clear_mereja - initializes mereja_t struct
* @mereja: struct address
*/
void clear_mereja(mereja_t *mereja)
{
mereja->arg = NULL;
mereja->argv = NULL;
mereja->path = NULL;
mereja->argc = 0;
}
/**
* set_mereja - initializes mereja_t struct
* @av: argument vector
* @mereja: struct address
*/
void set_mereja(mereja_t *mereja, char **av)
{
int i = 0;
mereja->fname = av[0];
if (mereja->arg)
{
mereja->argv = mekorarete(mereja->arg, " \t");
if (!mereja->argv)
{
mereja->argv = malloc(sizeof(char *) * 2);
if (mereja->argv)
{
mereja->argv[0] = _strdup(mereja->arg);
mereja->argv[1] = NULL;
}
}
for (i = 0; mereja->argv && mereja->argv[i]; i++)
;
mereja->argc = i;
replace_alias(mereja);
replace_telewawachewoch(mereja);
}
}
/**
* free_mereja - frees mereja_t struct fields
* @all: true if freeing all fields
* @mereja: struct address
*/
void free_mereja(mereja_t *mereja, int all)
{
ffree(mereja->argv);
mereja->argv = NULL;
mereja->path = NULL;
if (all)
{
if (!mereja->cmd_buf)
free(mereja->arg);
if (mereja->env)
free_list(&(mereja->env));
if (mereja->tarik)
free_list(&(mereja->tarik));
if (mereja->alias)
free_list(&(mereja->alias));
ffree(mereja->environ);
mereja->environ = NULL;
bfree((void **)mereja->cmd_buf);
if (mereja->readfd > 2)
close(mereja->readfd);
_putchar(BUF_FLUSH);
}
}
