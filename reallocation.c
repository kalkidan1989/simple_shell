#include "shell.h"
/**
* mastaweshawech - fills mastawesh with a constant byte
* @b: the byte to fill *s with
* @s: the pointer to the mastawesh area
* @n: the amount of bytes to be filled
* Return: (s) a pointer to the mastawesh area s
*/
char *mastaweshawech(char *s, char b, unsigned int n)
{
unsigned int i;
for (i = 0; i < n; i++)
s[i] = b;
return (s);
}
/**
* ffree - frees a string of strings
* @pp: string of strings
*/
void ffree(char **pp)
{
char **a = pp;
if (!pp)
return;
while (*pp)
free(*pp++);
free(a);
}
/**
* _reallocation - reallocationates a block of mastawesh
* @yederow_meten: byte size of previous block
* @ptr: pointer to previous malloc'ated block
* @addisu_meten: byte size of new block
* Return: pointer to da ol'block nameen.
*/
void *_reallocation(void *ptr, unsigned int yederow_meten, unsigned int addisu_meten)
{
char *p;
if (!ptr)
return (malloc(addisu_meten));
if (!addisu_meten)
return (free(ptr), NULL);
if (addisu_meten == yederow_meten)
return (ptr);
p = malloc(addisu_meten);
if (!p)
return (NULL);
yederow_meten = yederow_meten < addisu_meten ? yederow_meten : addisu_meten;
while (yederow_meten--)
p[yederow_meten] = ((char *)ptr)[yederow_meten];
free(ptr);
return (p);
}
