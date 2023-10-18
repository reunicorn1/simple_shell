#include "main.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * _getline - reads input from the sream and store it in a buffer
 * @lineptr: a pointer to a string
 * @n: number of bytes to be read
 * @stream: a file to read from
 * Return: number of bytes read from stream
 */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	int ch;
	size_t  i = 0;


	if (*lineptr == NULL || *n == 0)
	{
		*n = 1024;
		*lineptr = malloc(sizeof(char) * *n);
	if (*lineptr == NULL)
		return (-1);
	}
	while ((ch = fgetc(stream)) != EOF)
	{
		(*lineptr)[i] = (char)ch;
		i++;
		if (ch == '\n')
			break;
		if (i == *n - 1)
		{
			*lineptr = realloc(*lineptr, sizeof(char) * (2 * *n));
			if (*lineptr == NULL)
				return (-1);
			*n *= 2;
		}
	}
	if (ch == EOF && i == 0)
		return (-1);
	return ((ssize_t)i);
}
