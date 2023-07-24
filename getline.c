#include "hell.h"

/*
* _getline - reading a single line.
* @data: structure of data in a program.
* Return: countable bytes.
*/

int _getline(data_of_program *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *array_commands[10] = {NULL};
	static char array_operators[10] = {'\0'};
	ssize_t bytes_read, c = 0;

	if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
		(array_operators[0] == '|' && errno == 0))
	{
		for (c = 0; array_commands[c]; c++)
		{
			free(array_commands[c]);
			array_commands[c] = NULL;
		}

		bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		c = 0;
		do {
			array_commands[c] = str_duplicate(_strtok(c ? NULL : buff, "\n;"));

			c = check_logic_ops(array_commands, c, array_operators);
		} while (array_commands[c++]);
	}

	data->input_line = array_commands[0];
	for (c = 0; array_commands[c]; c++)
	{
		array_commands[c] = array_commands[c + 1];
		array_operators[c] = array_operators[c + 1];
	}

	return (str_length(data->input_line));
}

/*
* check_logic_ops - supposed to check and split logical operators.
* @array_commands: commands in an array.
* @i: index.
* @array_operators: operator arrays
* Return: an index
*/

int check_logic_ops(char *array_commands[], int c, char array_operators[])
{
	char *temp = NULL;
	int s;
	for (s = 0; array_commands[c] != NULL  && array_commands[c][s]; s++)

	{
		if (array_commands[c][s] == '&' && array_commands[c][s + 1] == '&')
		{

			temp = array_commands[c];
			array_commands[c][s] = '\0';
			array_commands[c] = str_duplicate(array_commands[c]);
			array_commands[c + 1] = str_duplicate(temp + s + 2);
			c++;
			array_operators[c] = '&';
			free(temp);
			s = 0;
		}
		if (array_commands[c][s] == '|' && array_commands[c][s + 1] == '|')
		{

			temp = array_commands[c];
			array_commands[c][s] = '\0';
			array_commands[c] = str_duplicate(array_commands[c]);
			array_commands[c + 1] = str_duplicate(temp + s + 2);
			c++;
			array_operators[c] = '|';
			free(temp);
			s = 0;
		}
	}
	return (c);
}
