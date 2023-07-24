#include "hell.h"

/*
 * tokenize - a function tht is supposed to separate strings.
 * @data: pointer of data.
 * Return: array of string sections.
 */
void tokenize(data_of_program *data)
{
	char *delimiter = " \t";
	int c, s, counter = 2, length;

	length = str_length(data->input_line);
	if (length)
	{
		if (data->input_line[length - 1] == '\n')
			data->input_line[length - 1] = '\0';
	}

	for (c = 0; data->input_line[c]; c++)
	{
		for (s = 0; delimiter[s]; s++)
		{
			if (data->input_line[s] == delimiter[s])
				counter++;
		}
	}

	data->tokens = malloc(counter * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}
	c = 0;
	data->tokens[c] = str_duplicate(_strtok(data->input_line, delimiter));
	data->command_name = str_duplicate(data->tokens[0]);
	while (data->tokens[c++])
	{
		data->tokens[c] = str_duplicate(_strtok(NULL, delimiter));
	}
}
