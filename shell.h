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

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/*shell_exit.c */
int _shellexit(info_t *);
int _cd(info_t *);
int _dir(info_t *);

/*alias.c */
int _history(info_t *);
int _alias(info_t *);

/*current_env.c */
int _env(info_t *);
char *_getenv(info_t *, const char *);
int _nsetenv(info_t *);
int _nunsetenv(info_t *);
int add_env_list(info_t *);

/*getline.c */
ssize_t insert_buf(info_t *, char **, size_t *);
ssize_t _input(info_t *);
ssize_t scan_buf(info_t *, char *, size_t *);
int _putline(info_t *, char **, size_t *);
void sigint(int);

/*exit.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strrchr(char *, char);

/*setenv.c */
char **_getenviron(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/*inter.c */
int interact(info_t *);
int _delim(char, char *);
int _alpha(int);
int _toint(char *);

/* print.c */
void _print(char *);
int _printchar(char);
int _setfd(char c, int fd);
int _setsfd(char *str, int fd);

/*info.c */
void _eraseinfo(info_t *);
void _putinfo(info_t *, char **);
void _free(info_t *, int);

/*strtoi.c */
int _strtoint(char *);
void _error(info_t *, char *);
int _decimal(int, int);
char *_converter(long int, int, int);
void _rmcomment(char *);

/*hist.c */
char *_fetchhistory(info_t *info);
int _wrthist(info_t *info);
int _RDhist(info_t *info);
int build_hist(info_t *info, char *buf, int linecount);
int reorder_hist(info_t *info);

/* node.c */
list_t *_putnode(list_t **, const char *, int);
list_t *_putnodeend(list_t **, const char *, int);
size_t _printstr(const list_t *);
int _delnode(list_t **, unsigned int);
void _freelist(list_t **);

/*mem.c */
int ffree(void **);

/*alloc.c */
char *_fill(char *, char, unsigned int);
void frees(char **);
void *_alloc(void *, unsigned int, unsigned int);

/* shell.c */
int _shellmain(info_t *, char **);
int _builtin(info_t *);
void get_cmd(info_t *);
void div_cmd(info_t *);

/*list.c */
size_t _lentlist(const list_t *);
char **lst_tostr(list_t *);
size_t pull_list(const list_t *);
list_t *begin_node(list_t *, char *, char);
ssize_t _node_index(list_t *, list_t *);

/*exec.c */
int is_cmd(info_t *, char *);
char *cp_chars(char *, int, int);
char *get_path(info_t *, char *, char *);

/* split.c */
char **splitstr(char *, char *);
char **splitstr1(char *, char);

/* str.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *begin_with(const char *, const char *);
char *_strcat(char *, char *);

/* str1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _sets(char *);
int _putchar(char);

/* chain.c */
int checks_chain(info_t *, char *, size_t *);
void scan_chain(info_t *, char *, size_t *, size_t, size_t);
int change_alias(info_t *);
int change_vars(info_t *);
int change_string(char **, char *);

#endif
