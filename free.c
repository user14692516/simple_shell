#include "hell.h"

/*
 * free_recurrent_data - freeing recurrent data on every loop.
 * @data: structure of the program in terms of data.
 * Return: NULL.
 */
void free_recurrent_data(data_of_program *data)
{
	if (data->tokens)
		free_array_of_pointers(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}

/*
 * free_all_data - freeing all the data.
 * @data: structure of the program in terms of data.
 * Return: NULL.
 */
void free_all_data(data_of_program *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	free_recurrent_data(data);
	free_array_of_pointers(data->env);
	free_array_of_pointers(data->alias_list);
}

/*
 * free_array_of_pointers - in the array it frees all the pointers.
 * Return: NULL
 */
void free_array_of_pointers(char **array)
{
	int c;

	if (array != NULL)
	{
		for (c = 0; array[c]; c++)
			free(array[c]);

		free(array);
		array = NULL;
	}
}
