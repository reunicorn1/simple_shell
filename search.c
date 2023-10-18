#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

/**
 * checkpoint - reads the array of strings and process it accordingly
 * @arg: is the array of pointers composing the tokens
 * @string: contains the raw user input
 * @count: the number of argument which are processed until now
 *
 * Return: a char which is somehow the path if required
 */

char *checkpoint(char **arg, char *string, int count)
{
	char *cmd;
	int err_code = error_stat(-16);

	if (_strcmp(arg[0], "exit") == 0)
	{
		if (arg[1] != NULL)
			err_code = exiting(arg[1], count);
		/*_alias(NULL, 0);*/
		free(string), free(arg), exit(err_code);
	}
	if (_strcmp(arg[0], "env") == 0)
	{
		error_stat(_env());
		return (arg[0]);
	}
	/*if (_strcmp(arg[0], "setenv") == 0)*/
	/*{*/
		/*error_stat(_setenv(arg));*/
		/*return (arg[0]);*/
	/*}*/
	/*if (_strcmp(arg[0], "unsetenv") == 0)*/
	/*{*/
		/*error_stat(_unsetenv(arg));*/
		/*return (arg[0]);*/
	/*}*/
	if (_strcmp(arg[0], "cd") == 0)
	{
		error_stat(_cd(arg[1]));
		return (arg[0]);
	}
	if (_strcmp(arg[0], "alias") == 0)
	{
		error_stat(_alias(arg, 0));
		return (arg[0]);
	} /* betty has an issue with number of lines */
	/*if (arg[0][0] == '/' || arg[0][0] == '.')*/
		/*return (arg[0]);*/
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
	char *fullpath = NULL;
	char *pathcopy = NULL, *token;

	if (!(arg[0] == '/' || arg[0] == '.'))
	{
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
			fullpath = _strcpy(fullpath, token);
			fullpath = _strcat(fullpath, "/");
			fullpath = _strcat(fullpath, arg);
			if (access(fullpath, X_OK) == 0)
			{
				free(pathcopy);
				return (fullpath);
			}
			token = strtok(NULL, ":");
		}
		free(fullpath);
		free(pathcopy);
		return (NULL);
	}
	else
	{
		if (access(arg, X_OK) == 0)
			return (arg);
		return (NULL);
	}
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
	else if (_strcmp(cmd, "cd") == 0)
		return (0);
	else if (_strcmp(cmd, "alias") == 0)
		return (0);
	else
		return (-1);
}
/**
 * semicolon_parser - prints a name as is
 * @next_ptr: the moving piece across letters
 *
 * Return: Nothing.
 */

void semicolon_parser(char ***next_ptr)
{
	int i, j; /*flag means that semicolon found*/
	static char *next_token;
	/*char *next_token;*/

	if (next_ptr == NULL)
	{
		next_token = NULL;
		return;
	}
	if (next_token)
		**next_ptr = next_token;
	for (i = 0; (*next_ptr)[i] != NULL; i++)
	{
		if (_strcmp((*next_ptr)[i], ";") == 0) /*semicolon found!*/
		{
			(*next_ptr)[i] = NULL;
			*next_ptr = &((*next_ptr)[i + 1]);
			return; /*returning a token, ready for the next*/
		}
		for (j = 0; (*next_ptr)[i][j] != '\0'; j++)
		{
			if ((*next_ptr)[i][j] == ';')
			{
				(*next_ptr)[i][j] = '\0';
				next_token = &((*next_ptr)[i][j + 1]);
				return;
			}
		}
	}
	*next_ptr = &((*next_ptr)[i]);
}
/**
 * cmd_list - send the array of commands to be executed
 * @array: is the raw array of tokens produced from input
 *
 * Return: the array only containing a one command with its arguments
 */

char **cmd_list(char **array)
{
	static char **next_ptr, **org;
	char **temp = NULL; /*a savepoint of where the cmd should start*/

	if (array != org) /*a new input*/
	{
		if (_strcmp(array[0], ";") == 0) /*checking if correct syntax*/
		{
			perror("syntax error near unexpected token `;'");
			return (NULL);
		}
		next_ptr = array;
		org = array;
		temp = array;
	}
	else
	{
		if (*next_ptr == NULL)  /*no next command to be passed*/
		{
			org = NULL;
			semicolon_parser(NULL);
			return (NULL);
		}
		temp = next_ptr; /*preparing the next command*/
	}
	semicolon_parser(&next_ptr);
	return (temp);
}
