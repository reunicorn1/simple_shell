#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"

/**
 * recieve_input - recieves input from the user
 *
 * Return: a string full on input
 */

char *recieve_input(void)
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
	printf("%d\n", input_len);
	if (input_len == -1)/*basically EOF*/
	{
		write(1, "This is end of file\n", 20);
		free(str);
		free(new_environ);
		exit(0);
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

	while (1)
	{
		if (i == 0)
			arr[i] = _strtok(str, " \t");
		else
			arr[i] = _strtok(NULL, " \t");
		if (arr[i] == NULL)
			break;
		i++;
	}
	return (arr);
}
