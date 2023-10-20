#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "main.h"


/**
 * alias_of_alias - checks the presence of an alias of an alias
 * @cmd: tha value that has been found in name array once
 * @name: is a pointer to the array of names of dataset
 * @value: is a pointer to the array of values of the dataset
 *
 * Return: a pointer to the value string matched
 */
char *alias_of_alias(char *cmd, char ***name, char ***value)
{
	int i, flag = 0;
	char *value_matched = NULL;

	for (i = 0; (*name)[i] != NULL; i++)
	{
		if (strcmp((*name)[i], cmd) == 0)
		{
			free(cmd);
			cmd = strdup((*value)[i]);
			value_matched = (*value)[i];
			if (!cmd)
				return (NULL);
			flag = 1;
			break;
		}
	}
	if (flag)
	{
		i = 0;
		while ((*name)[i] != NULL)
		{
			if (strcmp((*name)[i], cmd) == 0)
			{
				value_matched = (*value)[i];
				free(cmd);
				cmd = strdup((*value)[i]);
				if (!cmd)
					return (NULL);
				i = 0;
			}
			else
				i++;
		}
		free(cmd);
		return (value_matched);
	}
	free(cmd);
	return (NULL);
}

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
	int j, k, l;
	char *sub = NULL, *cmd = NULL, *value_matched = NULL;

	for (l = 0; (*string)[l] != '\0'; l++)
	{
		if ((*string)[l] == ' ')
			break;
	}
	cmd = malloc(sizeof(char) * (l + 1));
	if (!cmd)
		return (-1);
	cmd = strncpy(cmd, *string, l);
	cmd[l] = '\0';
	value_matched = alias_of_alias(cmd, name, value);
	if (value_matched)
	{
		sub = malloc(strlen(value_matched) + strlen(*string) - l + 1);
		if (!sub)
			return (-1);
		sub = strcpy(sub, value_matched);
		for (k = strlen(value_matched), j = l; (*string)[j] != '\0'; j++, k++)
			sub[k] = (*string)[j];
		sub[k] = '\0';
		free(*string);
		*string = sub;
	}
	return (0);
}
