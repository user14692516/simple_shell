#include "hell.h"

/*
 * _strtok - used to separate strings.
 * @line: array pointer.
 * @delim: characters that are marked off a string.
 * Return: pointer.
*/
char *_strtok(char *line, char *delim)
{
	int s;
	static char *str;
	char *copystr;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (s = 0; delim[s] != '\0'; s++)
		{
			if (*str == delim[s])
			break;
		}
		if (delim[s] == '\0')
			break;
	}
	copystr = str;
	if (*copystr == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (s = 0; delim[s] != '\0'; s++)
		{
			if (*str == delim[s])
			{
				*str = '\0';
				str++;
				return (copystr);
			}
		}
	}
	return (copystr);
}
