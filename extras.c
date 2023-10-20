#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "main.h"

/**
 * comment_out - it shortens the array of tokens by relacing # with NULL
 * @arg: the array of tokens
 *
 * Return: 0 always
 */

int comment_out(char **arg)
{
	int i;

	for (i = 0; arg[i] != NULL; i++)
	{
		if ((strcmp(arg[i], "#") == 0) || arg[i][0] == '#')
		{
			arg[i] = NULL;
			break;
		}
	}
	return (0);
}

/**
 * echo_dollar - handles the xases of $$, $? as well as envp
 * @arg: the array of tokens
 *
 * Return: 0 always
 */

int echo_dollar(char **arg)
{
	int i, j, exit = 0;
	pid_t ppid = 0;
	char *val = NULL, *ptr = NULL;

	if (arg[1][1] == '$')
	{
		ppid = getppid();
		printf("%d\n", ppid);
	}
	else if (arg[1][1] == '?')
	{
		exit = error_stat(-16);
		printf("%d\n", exit);
	}
	else
	{
		val = malloc(sizeof(char) * strlen(arg[1]));
		if (!val)
			return (-1);
		for (j = 0, i = 1; arg[1][i] != '\0'; i++, j++)
			val[j] = arg[1][i];
		val[j] = '\0';
		ptr = getenv(val);
		if (ptr)
			printf("%s\n", ptr);
		else
			printf("\n");
		free(val);
	}
	return (0);
}

/**
 * exit_with_code - exiting and freeing resources
 * @err_code: error code to be exited with
 * @count: the number of commands until now
 * @arg: the arguments array of tokens
 * @string: a tring to be freed
 *
 * Return: Nothing.
 */

void exit_with_code(int err_code, int count, char **arg, char *string)
{
	if (arg[1] != NULL)
		err_code = exiting(arg[1], count);
	free_grid(environ);
	_alias(NULL, 0);
	free(string);
	free(arg);
	exit(err_code);
}
