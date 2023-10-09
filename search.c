#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

/**
 * checkpoint - reads the array of strings and process it accordingly
 * @arg: is the array of pointers composing the tokens
 * @string: contains the raw user input
 *
 * Return: a char which is somehow the path if required
 */

char *checkpoint(char **arg, char *string)
{
	char *cmd, *code = "1";

	/* wildcard globing can occur here through a called function */
	if (_strcmp(arg[0], "exit") == 0)
	{
		if (arg[1] != NULL)
			code = arg[1];
		free(string);
		free(arg);
		free(new_environ);
		exit(_atoi(code));
	}
	if (_strcmp(arg[0], "env") == 0)
	{
		_env();
		return (arg[0]);
	}
	if (_strcmp(arg[0], "setenv") == 0)
	{
		_setenv(arg);
		return (arg[0]);
	}
	if (_strcmp(arg[0], "unsetenv") == 0)
	{
		_unsetenv(arg);
		return (arg[0]);
	}
	/* compare with other built in functions in the future here */
	if (arg[0][0] == '/')
		return (arg[0]);

	cmd = _which(arg[0]);
	return (cmd);
}

/**
 * _which - looks for the requried path
 * @arg: the argument which is the name of the executable
 *
 * Return: a string containing the fullpath, NULL on fsilure
 */

char *_which(char *arg)
{
	const char *variableName = "PATH";
	char *variableValue;
	char *fullpath;
	char *pathcopy, *token;

	fullpath = malloc(1024);
	if (fullpath == NULL)
		return (NULL);
	variableValue = getenv(variableName);
	pathcopy = _strdup(variableValue);
	if (pathcopy == NULL)
		return (NULL);
	token = strtok(pathcopy, ":");
	while (token != NULL)
	{
		_strcpy(fullpath, token);
		_strcat(fullpath, "/");
		_strcat(fullpath, arg);
		if (access(fullpath, X_OK) == 0)
		{
			free(pathcopy);
			return (fullpath);
		}
		token = strtok(NULL, ":");
	}
	free(pathcopy);
	return (NULL);
}

/**
 * is_builin - checks if a string matches one of the builin commands
 * @cmd: is the name of the builtin command
 *
 * Return: Nothing.
 */

int is_builin(char *cmd)
{
	if (_strcmp(cmd, "env") == 0)
		return (0);
	else if (_strcmp(cmd, "setenv") == 0)
		return (0);
	else if (_strcmp(cmd, "unsetenv") == 0)
		return (0);
	else
		return (-1);
}
