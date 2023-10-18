#include "main.h"
#include <stdarg.h>
/**
 * _printf - takes the format string and replaces the supported
 * directives by its equivalent argument
 * @format: the string to format
 * Return: the number characters printed to the screen
 */
int _printf(const char *format, ...)
{
	int i, count = 0;
	int (*func)(va_list *ap);
	char  c;
	va_list arg_list;
	va_list *va_ptr = &arg_list;

	if (format == 0)
		return (-1);
	if (*format == 0)
		return (0);

	va_start(arg_list, format);
	for (i = 0; i < _strlen((char *)format); i++)
	{
		if (format[i] != '%')
		{
			write(1, format + i, 1);
			count++;
		}
		else
		{
			if (!spy_cmp(format[i + 1]))
			{
				continue;
			}

			c = format[i + 1];
			func = get_format(c);
			if (func == NULL)
				printf("epic faliure :(");
			else
				count += func(va_ptr);
			count++;
			i++;
		}
	}
	va_end(arg_list);
	return (count);
}
