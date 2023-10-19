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

int _env(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		_printf("%s\n", environ[i]);
	}
	return (0);
}

/**
 * env_manipulation - manipulates the environ array
 * @newenv: the new element to be added
 * @i: number of elements to be copied from _environ
 *
 * Return: success 0, or failure -1
 */

int env_manipulation(char *newenv, int i)
{
	int j;
	char **new_environ = NULL;

	new_environ = (char **)malloc(sizeof(char *) * (i + 2));
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
	free(environ);
	environ = new_environ;
	return (0);
}

/**
 * _setenv - Initialize a new environ, or modify an existing one
 * @arg: a pointer to an array of pointers
 * @count: the number of commands until moment
 *
 * Return: return zero on success, or -1 on error
 */

int _setenv(char **arg, int count)
{
	char *newenv = NULL;
	int i;

	if (arg[1] == NULL || _strlen(arg[1]) == 0 || arg[1][0] == '=')
	{
		/*errno = EINVAL;*/
		/*fprintf(stderr, "./hsh: %d: setenv: ", count);*/
		/*perror("");*/
		return (-1);
	}
	if (arg[2] == NULL)
		return (_unsetenv(arg, count));
	newenv = malloc(sizeof(char) * (_strlen(arg[1]) + _strlen(arg[2]) + 2));
	if (newenv == NULL)
	{
		errno = ENOMEM;
		/*fprintf(stderr, "./hsh: %d: setenv: ", count);*/
		perror("");
		return (-1);
	}
	newenv[0] = '\0';
	newenv = _strcpy(newenv, arg[1]);
	newenv = _strcat(newenv, "=");
	newenv = _strcat(newenv, arg[2]);
	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], arg[1], _strlen(arg[1])) == 0)
		{
			if (_strcmp(environ[i], newenv) == 0)
			{
				free(newenv);
				return (0);
			}
			free(environ[i]);
			environ[i] = newenv;
			return (0);
		}
	}
	return (env_manipulation(newenv, i));
}

/**
 * _unsetenv - Remove an environment variable
 * @arg: a pointer to an array of pointers
 * @count: the number of commands until moment
 *
 * Return: zero on success, or -1 on error,
 */

int _unsetenv(char **arg, int count __attribute__((unused)))
{
	int n, m;

	if (arg[1] == NULL || _strlen(arg[1]) == 0 || arg[1][0] == '=')
	{
		/*errno = EINVAL;*/
		/*fprintf(stderr, "./hsh: %d: unsetenv: ", count);*/
		/*perror("");*/
		return (-1);
	}
	for (n = 0; environ[n] != NULL; n++)
	{
		if (_strncmp(environ[n], arg[1], _strlen(arg[1])) == 0)
		{
			free(environ[n]);
			environ[n] = NULL;
			for (m = n + 1; environ[m] != NULL; n++, m++)
				environ[n] = environ[m];
			environ[n] = NULL;
			return (0);
		}
	}
	return (0);
}

/**
 * exiting - process arguments for exiting
 * @arg: the argument which determines the status code
 * @count: the number of arguments until now
 *
 * Return: the status code to exit
 */

int exiting(char *arg, int count)
{
	int i;

	for (i = 0; i < (int)_strlen(arg); i++)
	{
		if (!(arg[i] > 47 && arg[i] < 58))
		{
			fprintf(stderr, "./hsh: %d: exit: Illegal number: %s\n", count, arg);
			return (2);
		}
	}
	return (_atoi(arg));
}
