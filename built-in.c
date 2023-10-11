#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "main.h"

/**
 * _env - prints the environment
 * @_environ: a pointer to an array of environment variables
 *
 * Return: Nothing.
 */

void _env(char ***_environ)
{
	int i;

	for (i = 0; (*_environ)[i] != NULL; i++)
	{
		_printf("%s\n", (*_environ)[i]);
	}
}

/**
 * _setenv - Initialize a new environ, or modify an existing one
 * @arg: a pointer to an array of pointers
 * @_environ: a pointer to the array of environment variables
 *
 * Return: return zero on success, or -1 on error
 */

int _setenv(char **arg, char ***_environ)
{
	char *newenv;
	int i, j;
	char **new_environ;

	if (arg[1] == NULL || _strlen(arg[1]) == 0 || arg[1][0] == '=')
	{
		errno = EINVAL;
		perror("");
		return (-1);
	}
	if (arg[2] == NULL)
		return (_unsetenv(arg, _environ));
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
	for (i = 0; (*_environ)[i] != NULL; i++)
	{
		if (_strncmp((*_environ)[i], arg[1], _strlen(arg[1])) == 0)
		{
			if (_strcmp((*_environ)[i], newenv) == 0)
			{
				free(newenv);
				return (0);
			}
			free(*_environ[i]);
			(*_environ)[i] = newenv;
			return (0);
		}
	}
	new_environ = (char **)malloc(sizeof(char *) * (i + 1));
	if (new_environ == NULL)
	{
		errno = ENOMEM;
		perror("");
		return (-1);
	}
	for (j = 0; j < i; j++)
		new_environ[j] = (*_environ)[j];
	new_environ[i] = newenv;
	new_environ[i + 1] = NULL;
	free(*_environ);
	*_environ = new_environ;
	return (0);
}

/**
 * _unsetenv - Remove an environment variable
 * @arg: a pointer to an array of pointers
 * @_environ: a pointer of an array of environment variables
 *
 * Return: zero on success, or -1 on error,
 */

int _unsetenv(char **arg, char ***_environ)
{
	int n, m;

	if (arg[1] == NULL || _strlen(arg[1]) == 0 || arg[1][0] == '=')
	{
		errno = EINVAL;
		perror("");
		return (-1);
	}
	for (n = 0; (*_environ)[n] != NULL; n++)
	{
		if (_strncmp((*_environ)[n], arg[1], _strlen(arg[1])) == 0)
		{
			for (m = n + 1; (*_environ)[n] != NULL; n++, m++)
				(*_environ)[n] = (*_environ)[m];
			return (0);
		}
	}
	return (0);
}
