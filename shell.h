#ifndef _SHELL_
#define _SHELL_

/*LIBRARIES*/
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

/*VARIABLE*/
extern char **environ;

/* MACROS */
#define DELIMITER " \t\r\n\a\""
#define ANALYZER(pos1, pos2) ((pos1 == '.' && pos2 == '/') \
		|| (pos1 == '/') || (pos1 == '.' && pos2 == '.'))

/*STRUCTURE*/
/**
 * struct directories - It's a structure whose function
 *                      is get directories names.
 * @directory: Directory name.
 * @next: Next node to traverse.
 */
typedef struct directories
{

	char *directory;
	struct directories *next;

} dir;
/**
 * struct built_in - It's a structure whose function
 *                      is get built-ins.
 * @b_in: Built-in name.
 * @function: Function to active in truth case.
 */
typedef struct built_in
{
	char *b_in;
	void (*function)();
} built_ins;

/*----PROTOTYPES----*/

/*STRING UTILITIES*/
char *_strdup(char *string);
size_t _strlen(char *string);
char *_strcat(char *src, char *dest);
int _strcmp(char *s1, char *s2);
char *_memcpy(char *dest, char *src, unsigned int n);
void _reverse(char *string);

/*BUILT-INS*/
int _builts(char *command, char *cmd, char *cmd2, int status);
void __exit(char *command, char *command2, int status);
void _env(void);

/*PRINTERS*/
void envi(void);
void _puts(char *string);
void _perror(char *shell_name, char *command, char *msg, int counter);
void print_integer(int integer);

/*MEMORY WORKERS*/
void *_calloc(unsigned int nmemb, unsigned int size);

/*COMMAND FINDERS*/
int recognize_command(char *command, int ext, int counter, char *shell_name);
int check_for_path(char **av, int counter, char *shell_name);
void check_flag(int flag, char *shell_name, char *command, int counter);
int find_fpth(char *command);
int exe_path(char **av);
int find_fname(char *command);
dir *path_helper(void);
int exe_fname(char **av);

/*LINKED LIST HELPERS*/
dir *add_node_end(dir **head, char *string);
void free_linked(dir *head);

/*SIGNAL HANDLERS*/
void signalHandler(int value);

/*GET ENVIRONMENT*/
char *_getenv(char *variable);

#endif /* _SHELL_ */
