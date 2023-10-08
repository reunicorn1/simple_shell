#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "main.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * recursive_int - prints the integer
 * @n: the number to be printed
 *
 * Return: number of numbers printed
 */
int recursive_int(int n)
{
	int n1;
	int count = 0;

	if (n < 0)
	{
		n1 = -n;
		_putchar('-');
		count++;
	}
	else
		n1 = n;
	count++;
	if (n1 / 10)
	{
		count = count + recursive_int(n1 / 10);
	}
	_putchar('0' + (n1 % 10));
	return (count);

}
/**
 * _printfint - handles the cases of %d, %i specifiers
 * @args: The specific argument
 *
 * Return: number of integers printed
 */

int _printfint(va_list args)
{
	int d, sum;

	d = va_arg(args, int);
	sum = recursive_int(d);
	return (sum);
}

/**
 * _printfstring - handles the cases of %s specifier
 * @args: the argument used
 *
 * Return: length of the string
 */

int _printfstring(va_list args)
{
	char *s;

	s = va_arg(args, char *);
	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (_strlen("(null)"));
	}
	write(1, s, _strlen(s));
	return (_strlen(s));
}

/**
 * _printf - takes a formatted string as input to produce output.
 * @format: formatted string, may or may not have placeholders.
 *
 * Return: returns the number of characters printed.
 */
int _printf(const char *format, ...)
{
	int i, j, flag, sum;
	va_list arg;
	int (*ptr)(va_list);
	print_fun f[] = {
	{"%s", _printfstring},
	{"%d", _printfint}
	};

	va_start(arg, format);
	if (format == NULL || (format[0] == '%' && format[1] == '\0'))
		return (-1);
	for (i = 0, sum = 0; format[i]; i++)
	{
		flag = 0;
		for (j = 0; j < 2; j++)
		{
			if (format[i] == f[j].form[0] && format[i + 1] == f[j].form[1])
			{
				ptr = f[j].f;
				sum += ptr(arg);
				i++;
				flag = 1;
				break;
			}
		}
		if (flag == 1)
			continue;
		if (format[i] == '%' && format[i + 1] == '%')
			i++;
		_putchar(format[i]);
		sum++;
	}
	va_end(arg);
	return (sum);
}
