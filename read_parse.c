#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"

/**
 * error_stat - returns the error stat according to input
 * @code: determines if we will take input stored or store a new one
 *
 * Return: the error status
 */

int error_stat(int code)
{
	static int status;

	if (code == -16) /*this is the code to extract the value stored*/
		return (status);
	status = code;
	return (code);
}

/**
 * recieve_input - recieves input from the user
 * @_environ: a pointer to an array of environment variables
 *
 * Return: a string full on input
 */

char *recieve_input(char ***_environ)
{
	size_t len = 1024;
	char *str = malloc(1024);
	int input_len;

	if (!str)
	{
		perror("Error: couldn't allocate memory\n");
		return (NULL);
	}
	input_len = getline(&str, &len, stdin);
	if (input_len == -1) /*basically EOF*/
	{
		if (isatty(STDIN_FILENO))
			write(1, "\n", 1);
		_alias(NULL, 0);
		free(str);
		free_grid(*_environ);
		exit(error_stat(-16));
	}
	str[input_len - 1] = '\0';
	_alias(&str, 1);
	return (str);
}

/**
 * toker - creates tokens out of the a string
 * @str: a string to be tokonized
 *
 * Return: an array of pointers
 */

char **toker(char *str)
{
	int i = 0;
	char **arr = malloc(sizeof(*arr) * 10);


	while (1)
	{
		if (i == 0)
		{
			arr[i] = strtok(str, " \t");
		}
		else
		{
			arr[i] = strtok(NULL, " \t");
		}
		if (arr[i] == NULL)
			break;
		i++;
	}
	return (arr);
}
