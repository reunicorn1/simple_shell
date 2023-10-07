#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
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

int execute(char **arg, char *cmd);
void loop(void);
char *recieve_input(void);
char **toker(char *str);
char *checkpoint(char **arg, char *string);
char *_which(char *arg);
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
void _env(void);
int _atoi(char *s);

#endif
