#include "hell.h"

/*
 * print_alias - supposed to edit aliases.
 * @data: structure of data in the program.
 * @alias: alias names that are supposed to be printed.
 * Return: 0
 */

int print_alias(data_of_program *data, char *alias)
{
	int c, s, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_length = str_length(alias);
		for (c = 0; data->alias_list[c]; c++)
		{
			if (!alias || (str_compare(data->alias_list[c], alias, alias_length)
				&&	data->alias_list[c][alias_length] == '='))
			{
				for (s = 0; data->alias_list[c][s]; s++)
				{
					buffer[s] = data->alias_list[c][s];
					if (data->alias_list[c][s] == '=')
						break;
				}
				buffer[s + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[c] + s + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/*
 * get_alias - tasked with editing the aliases.
 * @data: structure of data in the program.
 * @name: alias names.
 * Return: 0
 */
char *get_alias(data_of_program *data, char *name)
{
	int c, alias_length;

	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_length = str_length(name);

	for (c = 0; data->alias_list[c]; c++)
	{
		if (str_compare(name, data->alias_list[c], alias_length) &&
			data->alias_list[c][alias_length] == '=')
		{
			return (data->alias_list[c] + alias_length + 1);
		}
	}

	return (NULL);

}

/*
 * set_alias - editing aliases.
 * @alias_string: alias that has been set to a specific form.
 * @data: structure of data in the program.
 * Return: 0
 */

int set_alias(char *alias_string, data_of_program *data)
{
	int c, s;
	char buffer[250] = {'0'}, *temp = NULL;

	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);

	for (c = 0; alias_string[c]; c++)
		if (alias_string[c] != '=')
			buffer[c] = alias_string[c];
		else
		{
			temp = get_alias(data, alias_string + c + 1);
			break;
		}

	for (s = 0; data->alias_list[s]; s++)
		if (str_compare(buffer, data->alias_list[s], c) &&
			data->alias_list[s][c] == '=')
		{
			free(data->alias_list[s]);
			break;
		}

	if (temp)
	{
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		data->alias_list[s] = str_duplicate(buffer);
	}
	else 
		data->alias_list[s] = str_duplicate(alias_string);
	return (0);
}
