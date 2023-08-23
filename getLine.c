#include "shell.h"
/**
* input_buf - buffers chained commands
* @mereja: parameter struct
* @buf: address of buffer
* @len: address of len var
*
* Return: bytes read
*/
ssize_t input_buf(mereja_t *mereja, char **buf, size_t *len)
{
ssize_t r = 0;
size_t len_p = 0;
if (!*len) /* if nothing left in the buffer, fill it */
{
/*bfree((void **)mereja->cmd_buf);*/
free(*buf);
*buf = NULL;
signal(SIGINT, sigintHandler);
#if USE_GETLINE
r = getline(buf, &len_p, stdin);
#else
r = _getline(mereja, buf, &len_p);
#endif
if (r > 0)
{
if ((*buf)[r - 1] == '\n')
{
(*buf)[r - 1] = '\0'; /* remove trailing newline */
r--;
}
mereja->linecount_flag = 1;
comments_maseweged(*buf);
build_tarik_list(mereja, *buf, mereja->histcount++);
/* if (_strchr(*buf, ';')) is this a command chain? */
{
*len = r;
mereja->cmd_buf = buf;
}
}
}
return (r);
}
/**
* get_input - gets a line minus the newline
* @mereja: parameter struct
*
* Return: bytes read
*/
ssize_t get_input(mereja_t *mereja)
{
static char *buf; /* the ';' command chain buffer */
static size_t i, j, len;
ssize_t r = 0;
char **buf_p = &(mereja->arg), *p;
_putchar(BUF_FLUSH);
r = input_buf(mereja, &buf, &len);
if (r == -1) /* EOF */
return (-1);
if (len) /* we have commands left in the chain buffer */
{
j = i; /* init new iterator to current buf position */
p = buf + i; /* get pointer for return */
meyayaze(mereja, buf, &j, i, len);
while (j < len) /* iterate to semicolon or end */
{
if (is_chain(mereja, buf, &j))
break;
j++;
}
i = j + 1; /* increment past nulled ';'' */
if (i >= len) /* reached end of buffer? */
{
i = len = 0; /* reset position and length */
mereja->cmd_buf_type = CMD_NORM;
}
*buf_p = p; /* pass back pointer to current command position */
return (_strlen(p)); /* return length of current command */
}
*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
return (r); /* return length of buffer from _getline() */
}
/**
* read_buf - reads a buffer
* @i: size
* @mereja: parameter struct
* @buf: buffer
* Return: r
*/
ssize_t read_buf(mereja_t *mereja, char *buf, size_t *i)
{
ssize_t r = 0;
if (*i)
return (0);
r = read(mereja->readfd, buf, READ_BUF_SIZE);
if (r >= 0)
*i = r;
return (r);
}
/**
* _getline - gets the next line of input from STDIN
* @mereja: parameter struct
* @ptr: address of pointer to buffer, preallocationated or NULL
* @length: size of preallocationated ptr buffer if not NULL
* Return: s
*/
int _getline(mereja_t *mereja, char **ptr, size_t *length)
{
static char buf[READ_BUF_SIZE];
static size_t i, len;
size_t k;
ssize_t r = 0, s = 0;
char *p = NULL, *new_p = NULL, *c;
p = *ptr;
if (p && length)
s = *length;
if (i == len)
i = len = 0;
r = read_buf(mereja, buf, &len);
if (r == -1 || (r == 0 && len == 0))
return (-1);
c = _strchr(buf + i, '\n');
k = c ? 1 + (unsigned int)(c - buf) : len;
new_p = _reallocation(p, s, s ? s + k : k + 1);
if (!new_p) /* MALLOC FAILURE! */
return (p ? free(p), -1 : -1);
if (s)
_strncat(new_p, buf + i, k - i);
else
_strncpy(new_p, buf + i, k - i + 1);
s += k - i;
i = k;
p = new_p;
if (length)
*length = s;
*ptr = p;
return (s);
}
/**
* sigintHandler - blocks ctrl-C
* @sig_num: the signal number
* Return: void
*/
void sigintHandler(__attribute__((unused))int sig_num)
{
_puts("\n");
_puts("$ ");
_putchar(BUF_FLUSH);
}
