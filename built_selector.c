#include "shell.h"

/**
 * _builts - It checks for matches with built-ins.
 *
 * @command: Command dor checking.
 * @cmd: Command to free in exiting case.
 * @cmd2: Command to free in exiting case.
 * @status: Status for exiting.
 *
 * Return: Returns 0 on success, otherwise 1.
 */

int _builts(char *command, char *cmd, char *cmd2, int status)
{

	int i;
	built_ins built[] = {
		{"exit", __exit},
		{"envi", _env}
	};

	if (!command)
		return (0);

	for (i = 0; i < 2; i++)
		if (_strcmp(command, built[i].b_in) == 0)
		{
			(built[i].function)(cmd, cmd2, status);
			return (0);
		}

	return (1);
}
