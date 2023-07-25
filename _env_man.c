#include "hell.h"

/*
 * env_get_key - getting the value of a variable.
 * @key: the chosen variable.
 * @data: structure of data in the program.
 * Return: a value pointer of the variable.
 */
char *env_get_key(char *key, data_of_program *data)
{
	int c, key_length = 0;

	if (key == NULL || data->env == NULL)
		return (NULL);

	key_length = str_length(key);

	for (c = 0; data->env[c]; c++)
	{
	if (str_compare(key, data->env[c], key_length) &&
	data->env[c][key_length] == '=')
	{
		return (data->env[c] + key_length + 1);
		}
	}

	return (NULL);
}

/*
 * env_set_key - changing and creating the value of the variable.
 * @key: variable name.
 * @value: new number.
 * @data:structure of data in a program.
 * Return: 1 if NULL,2 in case of error and 0 for success
 */

int env_set_key(char *key, char *value, data_of_program *data)
{
	int c, key_length = 0, is_new_key = 1;

	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	key_length = str_length(key);

	for (c = 0; data->env[c]; c++)
	{
		if (str_compare(key, data->env[c], key_length) &&
		 data->env[c][key_length] == '=')
		{
			is_new_key = 0;

			free(data->env[c]);
			break;
		}
	}

	data->env[c] = str_concat(str_duplicate(key), "=");
	data->env[c] = str_concat(data->env[c], value);

	if (is_new_key)
	{

		data->env[c + 1] = NULL;
	}
	return (0);
}

/**
 * env_remove_key -  removing a key.
 * @key: key that is supposed to be removed.
 * @data: structure of data in the program.
 * Return: 1 for a removed key and 0 if key doesnt exist.
 */
int env_remove_key(char *key, data_of_program *data)
{
	int c, key_length = 0;

	if (key == NULL || data->env == NULL)
		return (0);

	key_length = str_length(key);

	for (c = 0; data->env[c]; c++)
	{
		if (str_compare(key, data->env[c], key_length) &&
		 data->env[c][key_length] == '=')
		{
			free(data->env[c]);
			c++;
			for (; data->env[c]; c++)
			{
				data->env[c - 1] = data->env[c];
			}

			data->env[c - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/*
 * print_environ - supposed to print the current environment.
 * @data: structure of data in the program.
 * Return: NULL
 */
void print_environ(data_of_program *data)
{
	int s;

	for (s = 0; data->env[s]; s++)
	{
		_print(data->env[s]);
		_print("\n");
	}
}
