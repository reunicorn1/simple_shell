#include <stdlib.h>
#include <stdio.h>
#include "main.h"


/**
 * new_alias - generates two strings of new data
 * @arg: the array of tokens
 * @s1: the index of arg[x] where '=' was found
 * @s2: the index of the string of arg
 *
 * Return: Nothing.
 */

alias_list *new_alias(char **arg, int s1, int s2)
{
	alias_list *a = NULL;
	int h, i = 0, j, k;

	while (arg[i] != NULL)
		i++;
	a = malloc(sizeof(alias_list));
	if (a == NULL)
		return (NULL);
	a->name = malloc(sizeof(char) * s2 + 1);
	if (a->name == NULL)
	{
		free(a);
		return (NULL);
	}
	a->name = strncpy(a->name, arg[s1], s2);
	a->name[s2] = '\0';
	a->value = malloc(sizeof(char) * 100);
	if (a->value == NULL)
	{
		free(a->name), free(a);
		return (NULL);
	}
	k = 0;
	for (h = s1, j = s2 + 1, k = 0; arg[h][j] != '\0'; j++, k++)
	{
		a->value[k] = arg[h][j];
	}
	a->value[k] = '\0';
	return (a);
}

/**
 * _alias_modify - modifies the list of aliases
 * @arg: the array of tokens
 * @name: a pointer to the array of names
 * @value: a pointer to the array of values
 * @s1: the index of arg[x] where '=' was found
 * @s2: the index of the arg to look in
 *
 * Return: -1 in failure, 1 in success.
 */

int _alias_modify(char **arg, char ***name, char ***value, int s1, int s2)
{
	int i;
	alias_list *b = NULL;

	b = new_alias(arg, s1, s2);
	if (b == NULL)
		return (-1);
	for (i = 0; (*name)[i] != NULL; i++)
	{
		if (strcmp((*name)[i], b->name) == 0)
		{
			free((*value)[i]);
			free(b->name);
			(*value)[i] = b->value;
			free(b);
			return (0);
		}
	}
	*name = (char **)realloc(*name, sizeof(char *) * (i + 2));
	if (*name == NULL)
		return (-1);
	*value = (char **)realloc(*value, sizeof(char *) * (i + 2));
	if (*value == NULL)
		return (-1);
	(*name)[i] = b->name;
	(*name)[i + 1] = NULL;
	(*value)[i] = b->value;
	(*value)[i + 1] = NULL;
	free(b);
	return (0);
}

/**
 * print_alias - printing the alias list or a certain element
 * @s: the specific name to be printed
 * @name: a pointer to the array of names
 * @value: a pointer to the array of values
 *
 * Return: always 0
 */

int print_alias(char *s, char ***name, char ***value)
{
	int i;

	for (i = 0; (*name)[i] != NULL; i++)
	{
		if (s == NULL)
			printf("%s='%s'\n", (*name)[i], (*value)[i]);
		else
		{
			if (strcmp((*name)[i], s) == 0)
			{
				printf("%s='%s'\n", (*name)[i], (*value)[i]);
				return (0);
			}
		}
	}
	return (0);
}

/**
 * alias_cont - checks parameters and send to corresponding functions
 * @arg: the array of tokens
 * @name: a pointer to the array of names
 * @value: a pointer to the array of values
 * @mode: the mode of processing
 *
 * Return: -1 in failure, 1 in success.
 */

int alias_cont(char **arg, char ***name, char ***value, int mode)
{
	if (arg == NULL)
	{
		if (name && value)
		{
			free_grid(*name);
			free_grid(*value);
		}
		return (0);
	}
	if (mode == 1)
	{
		alias_sub(arg, name, value);
		return (0);
	}
	if (!arg[1] || (strcmp(arg[1], "-p") == 0))
	{
		print_alias(NULL, name, value); /* prints the complete existing database t*/
		return (0);
	}
	return (1);
}

/**
 * _alias - aliases allow a string to be substituted for a word
 * @arg: the array of tokens
 * @mode: the mode of processing
 *
 * Return: -1 in failure, 1 in success.
 */

int _alias(char **arg, int mode)
{
	static char **name, **value;
	int i = 0, j = 1, flag;

	if (name == NULL)
	{
		name = malloc(sizeof(char *) * 1);
		if (!name)
			return (-1);
		name[0] = NULL;
	}
	if (value == NULL)
	{
		value = malloc(sizeof(char *) * 1);
		if (!value)
			return (-1);
		value[0] = NULL;
	}
	i = alias_cont(arg, &name, &value, mode);
	if (i == 1)
	{
		while (arg[j] != NULL)
		{
			flag = 0;
			for (i = 0; arg[j][i] != '\0'; i++)
			{
				if (arg[j][i] == '=') /* if '=' is found either edit or add to array */
				{
					_alias_modify(arg, &name, &value, j, i);
					flag = 1;
					break;
				}
			}
			if (!flag) /* if '=' not found */
				print_alias(arg[j], &name, &value);
			j++;
		} /*how to use return values from the mini functions?*/
	}
	return (0);
}
