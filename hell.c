#include "hell.h"

/*
 * main - it is supposed to declare a variable.
 * @argc: number of values.
 * @argv: values.
 * @env: command number of values.
 * Return: 0
 */
int main(int argc, char *argv[], char *env[])
{
	data_of_program data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	inicialize_data(data, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{/* terminal, interactive mode */
		errno = 2;/*???????*/
		prompt = PROMPT_MSG;
	}
	errno = 0;
	sisifo(prompt, data);
	return (0);
}

/*
 * handle_ctrl_c - output of the command that has been written.
 * @UNUSED: choice of the prototype
 */
void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/*
 * initialize_data - initializing the structure.
 * @data: written data
 * @argv: an array of arguments.
 * @env: env
 * @argc: command number of values.
 */
void inicialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int c = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;
	/* define the file descriptor to be readed*/
	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printe(data->program_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[c]; c++)
		{
			data->env[c] = str_duplicate(env[c]);
		}
	}
	data->env[c] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (c = 0; c < 20; c++)
	{
		data->alias_list[c] = NULL;
	}
}
/*
 * sisifo - an infinite loop output.
 * @prompt: output
 * @data: infinite data
 */
void sisifo(char *prompt, data_of_program *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		error_code = string_len = _getline(data);

		if (error_code == EOF)
		{
			free_all_data(data);
			exit(errno);
		}
		if (string_len >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenize(data);
			if (data->tokens[0])
			{ /* text is given to prompt, execute */
				error_code = execute(data);
				if (error_code != 0)
					_print_error(error_code, data);
			}
			free_recurrent_data(data);
		}
	}
}
