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

int recognize_command(char *command, int counter, char *shell_name)
{
	int status, traveler, rtrn = 0;
	char *av[9216] = {NULL};
	char cmd[9216] = {'\0'};

	if (!command || *command == '\n')
		return (0);
	for (; *command == ' ' || *command == '\t'; command++)
		;
	_memcpy(cmd, command, _strlen(command));

	traveler = 0;
	av[traveler] = strtok(cmd, DELIMITER);

	while (av[traveler++])
		av[traveler] = strtok(NULL, DELIMITER);

	if (!(*av)) /* Check if the given command is NULL after the split */
		return (0);
	if ((_strcmp(*av, "exit")) == 0)
		return (1);
	if ((_strcmp(*av, "env")) == 0)
	{
		envi();
		return (0);
	}

	status = check_for_path(av, counter, shell_name);
	if (status != 0)
	{
		if (status == 127)
			check_flag(3, shell_name, av[0], counter), rtrn = 127;
		else if (status == -1)
			rtrn = 2;
		else if (status == 126)
			check_flag(2, shell_name, av[0], counter), rtrn = 126;
	}
	return (rtrn);
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
			return (prcs);
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
			if (WEXITSTATUS(status) != 0)
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
		_perror(shell_name, command, "No such file or directory\n", counter);
		break;
	case 2:
		_perror(shell_name, command, "Permission denied\n", counter);
		break;
	case 3:
		_perror(shell_name, command, "not found\n", counter);
		break;
	}
}
