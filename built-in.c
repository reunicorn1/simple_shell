#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "main.h"

/**
 * _env - prints the environment
 *
 * Return: Nothing.
 */

void _env(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		_printf("%s\n", environ[i]);
	}
}

/**
 * _setenv - Initialize a new environ, or modify an existing one
 * @arg: a pointer to an array of pointers
 *
 * Return: return zero on success, or -1 on error
 */

int _setenv(char **arg)
{
	char *newenv;
	int i, j;
	static char **new_environ;

	if (arg[1] == NULL || _strlen(arg[1]) == 0 || arg[1][0] == '=')
	{
		errno = EINVAL;
		perror("");
		return (-1);
	}
	if (arg[2] == NULL)
		return (_unsetenv(arg));
	newenv = malloc(sizeof(char) * (_strlen(arg[1]) + _strlen(arg[2]) + 2));
	if (newenv == NULL)
	{
		errno = ENOMEM;
		perror("");
		return (-1);
	}
	_strcpy(newenv, arg[1]);
	_strcat(newenv, "=");
	_strcat(newenv, arg[2]);
	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], arg[1], _strlen(arg[1])) == 0)
		{
			if (_strcmp(environ[i], newenv) == 0)
			{
				free(newenv);
				return (0);
			}
			environ[i] = newenv;
			return (0);
		}
	}
	new_environ = (char **)_realloc(new_environ,
			sizeof(new_environ), sizeof(char *) * (i + 2));
	if (new_environ == NULL)
	{
		errno = ENOMEM;
		perror("");
		return (-1);
	}
	for (j = 0; j < i; j++)
		new_environ[j] = environ[j];
	new_environ[i] = newenv;
	new_environ[i + 1] = NULL;
	environ = new_environ;
	return (0);
}
/**
 * _unsetenv - Remove an environment variable
 * @arg: a pointer to an array of pointers
 *
 * Return: zero on success, or -1 on error,
 */

int _unsetenv(char **arg)
{
	int n, m;

	if (arg[1] == NULL || _strlen(arg[1]) == 0 || arg[1][0] == '=')
	{
		errno = EINVAL;
		perror("");
		return (-1);
	}
	for (n = 0; environ[n] != NULL; n++)
	{
		if (_strncmp(environ[n], arg[1], _strlen(arg[1])) == 0)
		{
			for (m = n + 1; environ[n] != NULL; n++, m++)
				environ[n] = environ[m];
			return (0);
		}
	}
	return (0);
}
