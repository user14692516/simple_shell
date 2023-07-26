#include "hell.h"

/*
 * builtins_list - execution.
 * @data: structure of data for the program.
 * Return: 1 Otherwise -1
 **/
int builtins_list(data_of_program *data)
{
	int z;
	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};


	for (z = 0; options[z].builtin != NULL; z++)
	{

		if (str_compare(options[z].builtin, data->command_name, 0))
		{

			return (options[z].function(data));
		}

	}
	return (-1);
}
