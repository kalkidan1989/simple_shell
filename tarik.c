#include "shell.h"
/**
* get_tarik_file - gets the tarik file
* @mereja: parameter struct
* Return: allocated string containg tarik file
*/
char *get_tarik_file(mereja_t *mereja)
{
char *buf, *dir;
dir = _getenv(mereja, "HOME=");
if (!dir)
return (NULL);
buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
if (!buf)
return (NULL);
buf[0] = 0;
_strcpy(buf, dir);
_strcat(buf, "/");
_strcat(buf, HIST_FILE);
return (buf);
}
/**
* write_tarik - creates a file, or appends to an existing file
* @mereja: the parameter struct
* Return: 1 on success, else -1
*/
int write_tarik(mereja_t *mereja)
{
ssize_t fd;
char *filename = get_tarik_file(mereja);
list_t *node = NULL;
if (!filename)
return (-1);
fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fd == -1)
return (-1);
for (node = mereja->tarik; node; node = node->next)
{
_putsfd(node->str, fd);
_putfd('\n', fd);
}
_putfd(BUF_FLUSH, fd);
close(fd);
return (1);
}
/**
* read_tarik - reads tarik from file
* @mereja: the parameter struct
* Return: histcount on success, 0 otherwise
*/
int read_tarik(mereja_t *mereja)
{
int i, last = 0, linecount = 0;
ssize_t fd, rdlen, fsize = 0;
struct stat st;
char *buf = NULL, *filename = get_tarik_file(mereja);
if (!filename)
return (0);
fd = open(filename, O_RDONLY);
free(filename);
if (fd == -1)
return (0);
if (!fstat(fd, &st))
fsize = st.st_size;
if (fsize < 2)
return (0);
buf = malloc(sizeof(char) * (fsize + 1));
if (!buf)
return (0);
rdlen = read(fd, buf, fsize);
buf[fsize] = 0;
if (rdlen <= 0)
return (free(buf), 0);
close(fd);
for (i = 0; i < fsize; i++)
if (buf[i] == '\n')
{
buf[i] = 0;
build_tarik_list(mereja, buf + last, linecount++);
last = i + 1;
}
if (last != i)
build_tarik_list(mereja, buf + last, linecount++);
free(buf);
mereja->histcount = linecount;
while (mereja->histcount-- >= HIST_MAX)
delete_node_at_index(&(mereja->tarik), 0);
renumber_tarik(mereja);
return (mereja->histcount);
}
/**
* build_tarik_list - adds entry to a tarik linked list
* @linecount: the tarik linecount, histcount
* @mereja: Structure containing potential arguments.
* @buf: buffer
* Return: Always 0
*/
int build_tarik_list(mereja_t *mereja, char *buf, int linecount)
{
list_t *node = NULL;
if (mereja->tarik)
node = mereja->tarik;
add_nodesehetetnd(&node, buf, linecount);
if (!mereja->tarik)
mereja->tarik = node;
return (0);
}
/**
* renumber_tarik - renumbers the tarik linked list after changes
* @mereja: Structure containing potential arguments.
* Return: the new histcount
*/
int renumber_tarik(mereja_t *mereja)
{
list_t *node = mereja->tarik;
int i = 0;
while (node)
{
node->num = i++;
node = node->next;
}
return (mereja->histcount = i);
}
