#include "hell.h"

int check_file(char *full_path);

/*
 * find_program - finding a program.
 * @data: pointer of data in a program.
 * Return: 0 for success
 */
int find_program(data_of_program *data)
{
	int c = 0, ret_code = 0;
	char **directories;

	if (!data->command_name)
		return (2);

	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (check_file(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	directories = tokenize_path(data);

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}
	for (c = 0; directories[c]; c++)
	{
		directories[c] = str_concat(directories[c], data->tokens[0]);
		ret_code = check_file(directories[c]);
		if (ret_code == 0 || ret_code == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(directories[c]);
			free_array_of_pointers(directories);
			return (ret_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(directories);
	return (ret_code);
}

/*
 * tokenize_path - tasked with tokenizing directory paths
 * @data: pointer to data in the program.
 * Return: path directories in an array
 */

char **tokenize_path(data_of_program *data)
{
	int c = 0;
	int counter_directories = 2;
	char **tokens = NULL;
	char *PATH;

	PATH = env_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = str_duplicate(PATH);

	for (c = 0; PATH[c]; c++)
	{
		if (PATH[c] == ':')
			counter_directories++;
	}

	tokens = malloc(sizeof(char *) * counter_directories);

	c = 0;
	tokens[c] = str_duplicate(_strtok(PATH, ":"));
	while (tokens[c++])
	{
		tokens[c] = str_duplicate(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}

/*
 * check_file - checking if a file exists
 * @full_path: name pointer.
 * Return: 0 for success.
 */

int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}
