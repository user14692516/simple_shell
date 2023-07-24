#include "hell.h"

/**
 * str_length - Outputs length of a str.
 * @string: ptr to str.
 * Return: ln of str.
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

/**
 * str_duplicate - duplicates an str
 * @string: str copy
 * Return: arr ptr
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

/**
 * str_compare - Compare string1 and string2
 * @string1: First string, shorter
 * @string2: Second str, longer
 * @number: num of char
 * Return: 1strings equals,0 difference in strings
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

/**
 * str_concat - concats two strs.
 * @string1: str to concat
 * @string2: str to concat
 *
 * Return: ptr to the array
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


/**
 * str_reverse - reverse a str.
 *
 * @string: ptr to str.
 * Return: void.
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
