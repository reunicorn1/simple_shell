#include "main.h"
#include <stdio.h>
#include <complex.h>

func_ptr get_format(char c)
{
	f_handler formats[] = {
	{"d", d_hand},
	{"c", c_hand},
	{"s", s_hand},
	{"%", percent_hand},
	{"i", i_hand},
	{NULL, NULL}
	};
	int i = 0;
	char *ptr = &c;

	while (i < 5)
	{
		if (*ptr == formats[i].spec[0])
			return (formats[i].f);
	i++;
	}
	return (NULL);
}

/**
 * spy_cmp - check if a charecter is special
 * @s1: a charecter
 * Return: 1 if the charecter is special
 */
int spy_cmp(char s1)
{
	int i = 0;

	char str[] = "disc%";

	while (i < 5)
	{
		if (str[i] == s1)
			return (1);

		i++;
	}
	return (0);
}

/**
 * print_number - prints am integer using _putchar
 * @n: the number to be printed
 * Return: void
 */

void print_number(int n)
{
	unsigned int number;
	char curr_char;

	if (n < 0)
	{
		n = -n;
		write(1, "-", 1);
	}

	number = n / 10;
	if (number)
		print_number(number);
	curr_char = n % 10 + 48;
	write(1, &curr_char, 1);
}

/**
 * digit_count - prints a number using write
 * @n: the number to print
 * Return: the amount of digits printed
 */
int digit_count(int n)
{
	unsigned int number, i = 0, if_neg = 0;

	if (n < 0)
	{
		n = n * (-1);
		if_neg = 1;

	}
	number = n;
	while (number)
	{
		number = number / 10;
		i++;
	}
	if (if_neg)
		return (i + 1);
	else
		return (i);
}
