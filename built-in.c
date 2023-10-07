#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "main.h"

extern char **environ;

/**
 * _env - prints the environment
 *
 * Return: Nothing.
 */

void _env(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		_printf("%s\n", environ[i]);
	}
}
