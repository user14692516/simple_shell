#include "hell.h"

/**
 * print_alias - this will  add, remove or show aliases
 * @data: struct for the program's data
 * @alias: name of the alias to be printed
 * Return: zero if sucess, or other number if its declared in the arguments
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

/**
 * get_alias - we continue to add, remove or show aliases
 * @data: struct for the program's data
 * @name: name of the requested alias.
 * Return: zero if sucess, or other number if its declared in the arguments
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

/**
 * set_alias - we add, or override alias
 * @alias_string: alias to be seted in the form (name='value')
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
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
