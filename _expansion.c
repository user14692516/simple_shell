#include "hell.h"

/*
 * expand_variables - tasked to expand variables.
 * @data: pointer of data of a program.
 * Return: NULL
 */

void expand_variables(data_of_program *data)
{
	int c, s;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	buffer_add(line, data->input_line);
	for (c = 0; line[c]; c++)
		if (line[c] == '#')
			line[c--] = '\0';
		else if (line[c] == '$' && line[c + 1] == '?')
		{
			line[c] = '\0';
			long_to_string(errno, expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + c + 2);
		}
		else if (line[c] == '$' && line[c + 1] == '$')
		{
			line[c] = '\0';
			long_to_string(getpid(), expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + c + 2);
		}
		else if (line[c] == '$' && (line[c + 1] == ' ' || line[c + 1] == '\0'))
			continue;
		else if (line[c] == '$')
		{
			for (s = 1; line[c + s] && line[c + s] != ' '; s++)
				expansion[s - 1] = line[c + s];
			temp = env_get_key(expansion, data);
			line[c] = '\0', expansion[0] = '\0';
			buffer_add(expansion, line + c + s);
			temp ? buffer_add(line, temp) : 1;
			buffer_add(line, expansion);
		}
	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/*
 * expand_alias - tasked with expanding the aliases.
 * @data: pointer of data for a program.
 * Return: NULL 
 */
void expand_alias(data_of_program *data)
{
	int c, s, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	buffer_add(line, data->input_line);

	for (c = 0; line[c]; c++)
	{
		for (s = 0; line[c + s] && line[c + s] != ' '; s++)
			expansion[s] = line[c + s];
		expansion[s] = '\0';

		temp = get_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + c + s);
			line[c] = '\0';
			buffer_add(line, temp);
			line[str_length(line)] = '\0';
			buffer_add(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/*
 * buffer_add - tasked with appending the string.
 * @buffer: buffer that is supposed to be filled.
 * @str_to_add: string that is supposed to be copied
 * Return: NULL
 */

int buffer_add(char *buffer, char *str_to_add)
{
	int length, c;

	length = str_length(buffer);
	for (c = 0; str_to_add[c]; c++)
	{
		buffer[length + c] = str_to_add[c];
	}
	buffer[length + c] = '\0';
	return (length + c);
}
