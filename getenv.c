#include "shell.h"
/**
* getsehetetnviron - returns the string array copy of our environ
* @mereja: Structure containing potential arguments.
* Return: Always 0
*/
char **getsehetetnviron(mereja_t *mereja)
{
if (!mereja->environ || mereja->env_changed)
{
mereja->environ = list_to_strings(mereja->env);
mereja->env_changed = 0;
}
return (mereja->environ);
}
/**
* _unmakenv - Remove an environment variable
* @mereja: Structure containing potential arguments.
* @var: the string env var property
* Return: 1 on delete, 0 otherwise
*/
int _unmakenv(mereja_t *mereja, char *var)
{
list_t *node = mereja->env;
size_t i = 0;
char *p;
if (!node || !var)
return (0);
while (node)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{
mereja->env_changed = delete_node_at_index(&(mereja->env), i);
i = 0;
node = mereja->env;
continue;
}
node = node->next;
i++;
}
return (mereja->env_changed);
}
/**
* _makenv - Initialize a new environment variable, or modify an existing one
* @mereja: Structure containing potential arguments.
* @value: the string env var value
* @var: the string env var property
* Return: Always 0
*/
int _makenv(mereja_t *mereja, char *var, char *value)
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
node = mereja->env;
while (node)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{
free(node->str);
node->str = buf;
mereja->env_changed = 1;
return (0);
}
node = node->next;
}
add_nodesehetetnd(&(mereja->env), buf, 0);
free(buf);
mereja->env_changed = 1;
return (0);
}
