#include "hell.h"

/*
 * long_to_string - converting a number to a string.
 * @number: number.
 * @string: string.
 * @base: converter of the base.
 *
 * Return: NULL
 */
void long_to_string(long number, char *string, int base)
{
	int index = 0, inNegative = 0;
	long cociente = number;
	char letters[] = {"0123456789abcdef"};

	if (cociente == 0)
		string[index++] = '0';

	if (string[0] == '-')
		inNegative = 1;

	while (cociente)
	{
		if (cociente < 0)
			string[index++] = letters[-(cociente % base)];
		else
			string[index++] = letters[cociente % base];
		cociente /= base;
	}
	if (inNegative)
		string[index++] = '-';

	string[index] = '\0';
	str_reverse(string);
}


/*
 * _atoi - A string of an integer.
 * @s: a pointer to a string.
 * Return: 0
 */
int _atoi(char *s)
{
	int sign = 1;
	unsigned int number = 0;
	/*1- the sign*/
	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		if (*s == '+')
			sign *= +1;
		s++;
	}

	/*2 - extract  number */
	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * sign);
}

/*
 * count_characters - counting characters of a string.
 * @string: pointer to a string.
 * @character: string that has characters.
 * Return: 0
 */
int count_characters(char *string, char *character)
{
	int c = 0, counter = 0;

	for (; string[c]; c++)
	{
		if (string[c] == character[0])
			counter++;
	}
	return (counter);
}
