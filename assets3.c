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
