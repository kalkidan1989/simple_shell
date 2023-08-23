#include "shell.h"
/**
* yenesehetetnv - prints the current environment
* @mereja: Structure containing potential arguments.
* Return: Always 0
*/
int yenesehetetnv(mereja_t *mereja)
{
print_list_str(mereja->env);
return (0);
}
/**
* _getenv - gets the value of an environ variable
* @mereja: Structure containing potential arguments.
* @name: env var name
* Return: the value
*/
char *_getenv(mereja_t *mereja, const char *name)
{
list_t *node = mereja->env;
char *p;
while (node)
{
p = starts_with(node->str, name);
if (p && *p)
return (p);
node = node->next;
}
return (NULL);
}
/**
* yenemakenv - Initialize a new environment variable,
* or modify an existing one
* @mereja: Structure containing potential arguments.
* Return: Always 0
*/
int yenemakenv(mereja_t *mereja)
{
if (mereja->argc != 3)
{
sehetetputs("Incorrect number of arguements\n");
return (1);
}
if (_makenv(mereja, mereja->argv[1], mereja->argv[2]))
return (0);
return (1);
}
/**
* yeneunmakenv - Remove an environment variable
* @mereja: Structure containing potential arguments.
* Return: Always 0
*/
int yeneunmakenv(mereja_t *mereja)
{
int i;
if (mereja->argc == 1)
{
sehetetputs("Too few arguements.\n");
return (1);
}
for (i = 1; i <= mereja->argc; i++)
_unmakenv(mereja, mereja->argv[i]);
return (0);
}
/**
* populatesehetetnv_list - populates env linked list
* @mereja: Structure containing potential arguments.
* Return: Always 0
*/
int populatesehetetnv_list(mereja_t *mereja)
{
list_t *node = NULL;
size_t i;
for (i = 0; environ[i]; i++)
add_nodesehetetnd(&node, environ[i], 0);
mereja->env = node;
return (0);
}
