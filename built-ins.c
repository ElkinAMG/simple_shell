#include "shell.h"

/**
 * __exit - Built-in exit
 *
 * @command: Command to free.
 * @command2: Command to free as well.
 * @status: Status for exiting.
 * Return: Nothing.
 */

void __exit(char *command, char *command2, int status)
{
	free(command2);
	free(command);
	exit(status);
}

/**
 * _env - Built-in print environment
 *
 * Return: Nothing.
 */

void _env(void)
{
	char **env;
	int i = 0;

	env = environ;

	for (; env[i]; i++)
	{
		write(STDOUT_FILENO, env[i], _strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}
