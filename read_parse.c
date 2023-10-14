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
	input_len = _getline(&str, &len, stdin);
	/*printf("%d\n", input_len);*/
	if (input_len == -1) /*basically EOF*/
	{
		write(1, "This is end of file\n", 20);
		free(str);
		free_grid(*_environ);
		exit(error_stat(-16));
	}
	str[input_len - 1] = '\0';
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

	/*printf("%s\n", str);*/
	while (1)
	{
		if (i == 0)
		{
			arr[i] = strtok(str, " \t");
			/*printf("[%s], i = %d\n", arr[i], i);*/
		}
		else
		{
			arr[i] = strtok(NULL, " \t");
			/*printf("[%s], i = %d\n", arr[i], i);*/
		}
		if (arr[i] == NULL)
			break;
		i++;
	}
	/*for (j = 0; j <= i; j++)*/
		/*printf("[%s], i = %d\n", arr[i], j);*/
	return (arr);
}

/**
 * is_input_eof - make sure if we reached eof in non interactive mode
 *
 * Return: Nothing.
 */

int is_input_eof(void)
{
	int c;

	c = fgetc(stdin);
	if (c == -1)
	{
		return (1);
	}
	ungetc(c, stdin);
	return (0);
}
