#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/**
 * alias_sub - substitues command if needed
 * @string: a pointer to the string
 * @name: is a pointer to the array of names of dataset
 * @value: is a pointer to the array of values of the dataset
 *
 * Return: success or failure
 */

int alias_sub(char **string, char ***name, char ***value)
{
	int i, j, k, l;
	char *sub, *cmd;

	for (l = 0; (*string)[l] != '\0'; l++)
	{
		if ((*string)[l] == ' ')
			break;
	}
	cmd = malloc(sizeof(char) * l + 1);
	if (!cmd)
		return (-1);
	_strncpy(cmd, *string, l);
	cmd[l] = '\0';
	for (i = 0; (*name)[i] != NULL; i++)
	{
		if (_strcmp((*name)[i], cmd) == 0)
		{
			sub = malloc(sizeof(char) * (strlen((*value)[i]) +
							(strlen(*string) - l)));
			if (!sub)
			{
				free(cmd);
				return (-1);
			}
			_strcpy(sub, (*value)[i]);
			for (k = _strlen((*value)[i]), j = l; (*string)[j] != '\0'; j++, k++)
				sub[k] = (*string)[j];
			sub[k] = '\0';
			free(*string);
			*string = sub;
			printf("%s\n", *string);
			break;
		}
	}
	free(cmd);
	return (0);
}
