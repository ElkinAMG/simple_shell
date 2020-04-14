#include "shell.h"

/**
 * recognize_command - It make the job of cut the command
 *                     and pass it to checker.
 * @command: The current command with its arguments.
 * @counter: Receives the current number that have the counter of commands.
 * @shell_name: Receives the current shell name.
 *
 * Return: It returns nothing.
 */

void recognize_command(char *command, int counter, char *shell_name)
{
	int status, traveler;
	char *av[1024] = {NULL};
	char cmd[1024] = {'\0'};

	if (!command || *command == '\n')
		return;

	/*Travels through command parameter until*/
	/*There are not spaces in it*/
	for (; *command == ' ' || *command == '\t'; command++)
		;

	_memcpy(cmd, command, _strlen(command));

	traveler = 0;
	av[traveler] = strtok(cmd, DELIMITER);

	while (av[traveler++])
		av[traveler] = strtok(NULL, DELIMITER);

	if (!(*av)) /* Check if the given command is NULL after the split */
		return;

	status = check_for_path(av, counter, shell_name);
	if (status != 0)
	{
		if (status == 127)
		{
			_perror(shell_name, av[0], "not found\n", counter);
			return;
		}
		if (status == -1)
		{
			_perror(shell_name, av[0], "has occured an error\n", counter);
			return;
		}
		if (status == 126)
			check_flag(2, shell_name, av[0], counter);
	}

}

/**
 * check_for_path - Check everything to know about the command.
 *                         (PERMISSIONS/EXISTENCE)
 * @av: Array of arguments that will be executed with the command.
 * @counter: Receives the current number that have the counter of commands.
 * @shell_name: Receives the current shell name.
 *
 * Return: It return the status of the given command that serves
 *         for recognize processes, on failure returns -3.
 */

int check_for_path(char **av, int counter, char *shell_name)
{
	int status, flag, prcs;
	pid_t n_pid = 0;

	prcs = find_fpth(*av);
	if (prcs != 0)
	{
		if (prcs == 126)
			return (prcs); /* if prcs is equals to 2 the use do not have permissions. */
		prcs = find_fname(*av);
		if (prcs != 0)
			return (prcs);
	}

	n_pid = fork();

	if (n_pid >= 0)
	{
		if (n_pid == 0)
		{
			flag = exe_path(av);
			if (flag != 0)
			{
				flag = exe_fname(av);
				if (flag != 0)
					check_flag(flag, shell_name, av[0], counter);
			}
			exit(0);
		}
		else
		{
			wait(&status);
			if (status < 0)
				return (-1);
			return (0);
		}
	}

	_perror(shell_name, av[0], "Error with creation subprocess\n", counter);
	return (1);
}

/**
 * check_flag - Used for print error messages.
 * @flag: Receives the flag that identifies the error process.
 * @shell_name: Receives the current shell name.
 * @command: Receives the executed command.
 * @counter: Receives the current number that have the counter of commands.
 *
 * Return: It returns nothing.
 */

void check_flag(int flag, char *shell_name, char *command, int counter)
{
	switch (flag)
	{
		case 1:
			_perror(shell_name, command, "has occured an error\n", counter);
			break;
		case 2:
			_perror(shell_name, command, "Permission denied\n", counter);
			break;
	}
}