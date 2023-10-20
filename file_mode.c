#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

/**
 * readfile - recieves input from the user
 * @stream: afile pointer to where to extract data
 *
 * Return: a string full on input
 */

char *readfile(FILE *stream)
{
	size_t len = 1024;
	char *str = malloc(1024);
	int input_len;

	if (!str)
	{
		perror("Error: couldn't allocate memory\n");
		return (NULL);
	}
	input_len = getline(&str, &len, stream);
	if (input_len == -1) /*basically EOF*/
	{
		free(str);
		free_grid(environ);
		fclose(stream);
		exit(error_stat(-16));
	}
	str[input_len - 1] = '\0';
	return (str);
}

/**
 * file_mode - it's the simple shell working from a file
 * @av: array of argument vector
 *
 * Return: Nothing.
 */

void file_mode(char **av)
{
	char *input_str = NULL;
	char **arg = NULL;
	int status = 0, count = 0, error = 0, fd = 0;
	FILE *stream = NULL;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		fprintf(stderr, "%s: %d: Can't open %s\n", av[0], count, av[1]);
		free_grid(environ);
		exit(127);
	}
	else
	{
		stream = fdopen(fd, "r");
		while (1)
		{
			error_stat(error), count++;
			input_str = readfile(stream); /* getline in the hood */
			arg = toker(input_str); /* tokonize the input */
			if (arg[0] != NULL)
			{
				status = command_runner(arg, input_str, count, &error, &av[0]);
			}
			if (status != -1) /*return here to review this condition*/
			{
				/* freeing memory */
				free(input_str);
				free(arg);
			}
		}
	}
}
