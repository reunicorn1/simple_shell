#include "main.h"

/**
 * _atoi - convert a string to an integer
 * @s: a string which is  apointer of char
 *
 * Description: this function convert a string to an integer
 * Return: the converted integer
 */

int _atoi(char *s)
{
	unsigned int i, j, n, p, result;

	i = 0;
	result = 0;
	n = 0;
	p = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	for (j = 0; j < i; j++)
	{
		if (s[j] == '-')
			n++;
		if (s[j] == '+')
			p++;
		if (s[j] > 47 && s[j] < 58)
		{
			result = result * 10 + (s[j] - 48);
		}
		if (!(s[j] > 47 && s[j] < 58) && result > 0)
			break;
	}
	if (n > p || p > n)
		result = -result;
	if (result == 0)
		return (0);
	else
		return (result);
}

/**
 * _strncmp -  compares two strings
 * @s1: is a variable of string type
 * @s2: is a variable of string type
 * @n: the number of letters to be comapred
 *
 * Description: this function compares two strings
 * Return: 0 if equal, +ve if s1 is larger, -ve if s1 is smaller
 */

int _strncmp(char *s1, char *s2, size_t n)
{
	size_t i;

	if (s1 == NULL && s2 == NULL)
		return (0);
	else if (s1 == NULL)
		return (-1);
	else if (s2 == NULL)
		return (1);
	for (i = 0; i < n && s1[i] != '\0' && s2[i] != '\0'; i++)
	{
		if (s1[i] - s2[i] != 0)
			return ((int)(s1[i] - s2[i]));
	}
	if ((i == n) || (s1[i] == '\0' && s2[i] == '\0'))
		return (0);
	if (s1[i] == '\0')
		return (-1);
	else
		return (1);
}

/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: is a pointer to the memory previously allocated
 * @old_size: is a variable of innt type
 * @new_size: is a variable of int type
 *
 * Description: this function reallocates a memory block using malloc
 * Return: pinter to the new memory
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr;

	if (new_size == old_size)
		return (ptr);
	/* allocation of new memory */
	if (new_size > 0 || ptr == NULL)
	{
		new_ptr = malloc(new_size);
		if (new_ptr == NULL)
			return (NULL);
	}
	/* copying process */
	if (ptr != NULL && new_size > 0)
	{
		if (new_size < old_size)
			old_size = new_size;
		memcpy(new_ptr, ptr, old_size);
	}
	/* freeing process */
	if (ptr != NULL)
		free(ptr);
	if (new_size == 0 && ptr != NULL)
		return (NULL);
	return (new_ptr);
}

/**
 * free_grid - frees a 2 dimensional grid
 * @grid: a two dimentional array previously created
 *
 * Description: this function  frees a 2 dimensional grid
 * Return: non
 */

void free_grid(char **grid)
{
	int i;

	for (i = 0; grid[i] != NULL; i++)
		free(grid[i]);
	free(grid);
}
