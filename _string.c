#include "hell.h"

/*
 * str_length - givin the string length.
 * @string: string pointer.
 * Return: string length.
 */
int str_length(char *string)
{
	int length = 0;

	if (string == NULL)
		return (0);

	while (string[length++] != '\0')
	{
	}
	return (--length);
}

/*
 * str_duplicate - duplicating a string
 * @string: a copy of a string.
 * Return: an array pointer.
 */
char *str_duplicate(char *string)
{
	char *result;
	int length, c;

	if (string == NULL)
		return (NULL);

	length = str_length(string) + 1;

	result = malloc(sizeof(char) * length);

	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (c = 0; c < length ; c++)
	{
		result[c] = string[c];
	}

	return (result);
}

/*
 * str_compare - comparing strings.
 * @string1: first string.
 * @string2: second string.
 * @number: character number.
 * Return: 1
 */
int str_compare(char *string1, char *string2, int number)
{
	int iterator;

	if (string1 == NULL && string2 == NULL)
		return (1);

	if (string1 == NULL || string2 == NULL)
		return (0);

	if (number == 0) /* infinite longitud */
	{
		if (str_length(string1) != str_length(string2))
			return (0);
		for (iterator = 0; string1[iterator]; iterator++)
		{
			if (string1[iterator] != string2[iterator])
				return (0);
		}
		return (1);
	}
	else /* if there is a number of chars to be compared */
	{
		for (iterator = 0; iterator < number ; iterator++)
		{
			if (string1[iterator] != string2[iterator])
			return (0);
		}
		return (1);
	}
}

/*
 * str_concat - conccting two strings.
 * @string1: first string to the conact.
 * @string2: second string to the conact
 *
 * Return: array pointer.
 */
char *str_concat(char *string1, char *string2)
{
	char *result;
	int length1 = 0, length2 = 0;

	if (string1 == NULL)
		string1 = "";
	length1 = str_length(string1);

	if (string2 == NULL)
		string2 = "";
	length2 = str_length(string2);

	result = malloc(sizeof(char) * (length1 + length2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	/* copy of string1 */
	for (length1 = 0; string1[length1] != '\0'; length1++)
		result[length1] = string1[length1];
	free(string1);

	/* copy of string2 */
	for (length2 = 0; string2[length2] != '\0'; length2++)
	{
		result[length1] = string2[length2];
		length1++;
	}

	result[length1] = '\0';
	return (result);
}


/*
 * str_reverse - reversing a string.
 * @string: string pointer.
 * Return: NULL
 */
void str_reverse(char *string)
{

	int c = 0, length = str_length(string) - 1;
	char hold;

	while (c < length)
	{
		hold = string[c];
		string[c++] = string[length];
		string[length--] = hold;
	}
}
