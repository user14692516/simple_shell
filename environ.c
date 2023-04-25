#include "main.h"

/**
 * _myenv - This one prints the current environment
 * @info: This is Structure containing potential arguments.
 * It is used to maintain constant function prototype.
 * Return: This will Always return a 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - getenv gets the value of an environ variable
 * @info: This is the Structure containing potential arguments.
 * It is used to maintain constant function prototype.
 * @name: name is the env variable name
 *
 * Return: The function will return the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - mysetenv will Initialise a new environment variable,
 *             or it will modify an existing one
 * @info: This is the Structure containing potential arguments.
 * It is used to maintain constant function prototype.
 * Return: The function will Always return 0.
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - It will Remove an environment variable
 * @info: This is the Structure containing potential arguments.
 * It is used to maintain constant function prototype.
 * Return: This will Always 0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - This one populates env linked list
 * @info: This is Structure containing potential arguments.
 *  It is used to maintain constant function prototype.
 * Return: This will Always return 0.
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
