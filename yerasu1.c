#include "shell.h"
/**
* yene_tarike - displays the tarik list, one command by line,
* proceeded with line numbers, starting at 0.
* @mereja: Structure containing potential arguments.
* Return: Always 0
*/
int yene_tarike(mereja_t *mereja)
{
print_list(mereja->tarik);
return (0);
}
/**
* unalias_maker - sets alias to string
* @mereja: parameter struct
* @str: the string alias
* Return: Always 0 on success, 1 on error
*/
int unalias_maker(mereja_t *mereja, char *str)
{
char *p, c;
int ret;
p = _strchr(str, '=');
if (!p)
return (1);
c = *p;
*p = 0;
ret = delete_node_at_index(&(mereja->alias),
get_node_index(mereja->alias, node_starts_with(mereja->alias, str, -1)));
*p = c;
return (ret);
}
/**
* alias_maker - sets alias to string
* @mereja: parameter struct
* @str: the string alias
* Return: Always 0 on success, 1 on error
*/
int alias_maker(mereja_t *mereja, char *str)
{
char *p;
p = _strchr(str, '=');
if (!p)
return (1);
if (!*++p)
return (unalias_maker(mereja, str));
unalias_maker(mereja, str);
return (add_nodesehetetnd(&(mereja->alias), str, 0) == NULL);
}
/**
* alias_aweta - prints an alias string
* @node: the alias node
* Return: Always 0 on success, 1 on error
*/
int alias_aweta(list_t *node)
{
char *p = NULL, *a = NULL;
if (node)
{
p = _strchr(node->str, '=');
for (a = node->str; a <= p; a++)
_putchar(*a);
_putchar('\'');
_puts(p + 1);
_puts("'\n");
return (0);
}
return (1);
}
/**
* yene_alias - mimics the alias yerasu (man alias)
* @mereja: Structure containing potential arguments.
* Return: Always 0
*/
int yene_alias(mereja_t *mereja)
{
int i = 0;
char *p = NULL;
list_t *node = NULL;
if (mereja->argc == 1)
{
node = mereja->alias;
while (node)
{
alias_aweta(node);
node = node->next;
}
return (0);
}
for (i = 1; mereja->argv[i]; i++)
{
p = _strchr(mereja->argv[i], '=');
if (p)
alias_maker(mereja, mereja->argv[i]);
else
alias_aweta(node_starts_with(mereja->alias, mereja->argv[i], '='));
}
return (0);
}
