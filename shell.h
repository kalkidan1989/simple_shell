#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for wede_quter() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define HIST_FILE	".simple_shell_tarik"
#define HIST_MAX	4096

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

extern char **environ;


/**
 * struct zerzerochtr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct zerzerochtr
{
	int num;
	char *str;
	struct zerzerochtr *next;
} list_t;

/**
 * struct passmereja - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @tarik: the tarik node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @readfd: the fd from which to read line input
 * @histcount: the tarik line number count
 */
typedef struct passmereja
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *tarik;
	list_t *alias;
        list_t *env;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for mastawesh mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} mereja_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct yerasu - contains a yerasu string and related function
 * @type: the yerasu command flag
 * @func: the function
 */
typedef struct yerasu
{
	char *type;
	int (*func)(mereja_t *);
} yerasu_table;


/* toem_shloop.c */
int hsh(mereja_t *, char **);
int find_yerasu(mereja_t *);
void find_cmd(mereja_t *);
void fork_cmd(mereja_t *);

/* toem_alawekem.c */
int cmd_niew(mereja_t *, char *);
char *fiidel_mabizate(char *, int, int);
char *find_path(mereja_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_sehetet.c */
void sehetetputs(char *);
int sehetetputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toemsehetetxits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_mekefafel.c */
char **mekorarete(char *, char *);
char **mekorarete2(char *, char);

/* toem_reallocation.c */
char *mastaweshawech(char *, char, unsigned int);
void ffree(char **);
void *_reallocation(void *, unsigned int, unsigned int);

/* toem_mastawesh.c */
int bfree(void **);

/* toemkale.c */
int interactive_mode(mereja_t *);
int is_delim(char, char *);
int _isalpha(int);
int kale(char *);

/* toem_sehetet1.c */
int sehetetrratoi(char *);
void printsehetetrror(mereja_t *, char *);
int print_d(int, int);
char *wede_quter(long int, int, int);
void comments_maseweged(char *);

/* toem_yerasu.c */
int yeneexit(mereja_t *);
int mahider_mekeyer(mereja_t *);
int yenesehetetrdata(mereja_t *);

/* toem_yerasu1.c */
int yene_tarike(mereja_t *);
int yene_alias(mereja_t *);

/*toem_getline.c */
ssize_t get_input(mereja_t *);
int _getline(mereja_t *, char **, size_t *);
void sigintHandler(int);

/* toemsehetetnviron.c */
char *_getenv(mereja_t *, const char *);
int yenesehetetnv(mereja_t *);
int yenemakenv(mereja_t *);
int yeneunmakenv(mereja_t *);
int populatesehetetnv_list(mereja_t *);

/* toem_getmereja.c */
void clear_mereja(mereja_t *);
void set_mereja(mereja_t *, char **);
void free_mereja(mereja_t *, int);

/* toem_getenv.c */
char **getsehetetnviron(mereja_t *);
int _unmakenv(mereja_t *, char *);
int _makenv(mereja_t *, char *, char *);

/* toem_tarik.c */
char *get_tarik_file(mereja_t *mereja);
int write_tarik(mereja_t *mereja);
int read_tarik(mereja_t *mereja);
int build_tarik_list(mereja_t *mereja, char *buf, int linecount);
int renumber_tarik(mereja_t *mereja);

/* toem_zerzeroch.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_nodesehetetnd(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_zerzeroch1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_telewawachewoch.c */
int is_chain(mereja_t *, char *, size_t *);
void meyayaze(mereja_t *, char *, size_t *, size_t, size_t);
int replace_alias(mereja_t *);
int replace_telewawachewoch(mereja_t *);
int replace_string(char **, char *);

#endif
