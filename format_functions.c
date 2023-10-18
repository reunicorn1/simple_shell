#include "main.h"
#include <stdio.h>
/**
 * c_hand - handles a charecter argument
 * @ap: a va_list
 * Return: one
 */
int c_hand(va_list *ap)
{
	char c = va_arg(*ap, int);

	write(1, &c, 1);
	return (1);
}

/**
 * s_hand - handles a string argumetn
 * @ap: a va_list
 * Return: the lenght of the string
 */
int s_hand(va_list *ap)
{
	char *c = (char *)va_arg(*ap, char *);

	write(1, c, strlen(c));
	return (strlen(c));
}

/**
 * percent_hand - handles a percent charecter
 * Return: nothing
 */
int percent_hand(void)
{

	write(1, "%", 1);
	return (1);
}

/**
 * i_hand - handles an intiger argument
 * @ap: a va_list
 * Return: number of digits in the number
 */
int i_hand(va_list *ap)
{
	int num = va_arg(*ap, int);

	print_number(num);
	return (digit_count(num));
}

/**
 * d_hand - handles a decimal arguemnt
 * @ap: a va_list
 * Return: number of digits in the number
 */
int d_hand(va_list *ap)
{
	int num = va_arg(*ap, int);

	print_number(num);
	return (digit_count(num));
}
