#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * struct print_fun - Struct print_fun
 *
 * @form: The specifier format
 * @f: The function associated
 */
typedef struct print_fun
{
	char *form;
	int (*f)(va_list args);
} print_fun;

int execute(char **arg, char *cmd, char ***_environ);
void loop(char ***_environ);
char *recieve_input(char ***_environ);
char **toker(char *str);
char *checkpoint(char **arg, char *string, char ***_environ, int count);
char *_which(char *arg);
int is_builin(char *cmd);
int is_input_eof(void);
char **cmd_list(char **array);
int error_stat(int code);

/*our own version of functions*/
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char *_strtok(char *str, char *dlm);
int is_dlm(int c, const char *dlm);

/*string manipulation functons*/
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
int _strlen(char *s);
int _putchar(char c);
int recursive_int(int n);
int _printfint(va_list args);
int _printfstring(va_list args);
int _printf(const char *format, ...);
int _atoi(char *s);
int _strncmp(char *s1, char *s2, size_t n);

/* printing error functions*/
int _putchar2(char c);
int recursive_int2(int n);
int _printfint2(va_list args);
int _printfstring2(va_list args);
int _printferror(const char *format, ...);

/*built-in functions*/
void _env(char ***_environ);
int _setenv(char **arg, char ***_environ);
int _unsetenv(char **arg, char ***_environ);
int _cd(char *path);
int exiting(char *arg, int count);

void free_grid(char **grid);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

#endif
