#include "shell.h"

/**
 * find_fpth - It looks for the binary via full path.
 * @command: The current command.
 *
 * Return: It returns 0 on success, returns 1 if the file is a directory,
 * return 2 if the file do not have permissions, on failure 1.
 */

int find_fpth(char *command)
{
	struct stat st;

	/* Checks if the command starts with './' || '/' || '.' */
	if (ANALYZER(command[0], command[1]))
	{
		if (stat(command, &st) == 0)
		{
			if ((st.st_mode & __S_IFREG) && !access(command, X_OK))
				return (0);
			else
				return (126);
		}
	}

	return (127);
}

/**
 * exe_path - It executes the given command via full path.
 * @av: Array of arguments with the current command.
 *
 * Return: It returns 0 on success, otherwise returns 1.
 */

int exe_path(char **av)
{
	/* Check if the command starts with ./ or / */
	if (execve(av[0], av, environ) != -1)
		return (0);

	return (127);
}

/**
 * path_helper - It creates new nodes with each directory in PATH.
 *
 * Return: It returns a pointer to a structure dir.
 */

dir *path_helper(void)
{

	dir *directories_struct = NULL;
	int directory_num, iter;
	char *path = NULL;
	char *div[1024] = {NULL};

	directory_num = 0;
	path = _getenv("PATH");

	if (*path == ':' || *path == '\0')
	{
		div[directory_num++] = ".";
	}

	div[directory_num] = strtok(path, " :\n\t\r\0");

	while (div[directory_num++] != NULL)
		div[directory_num] = strtok(NULL, " :\n\t\r\0");

	for (iter = 0; iter < (directory_num - 1); iter++)
		add_node_end(&directories_struct, div[iter]);

	free(path);
	return (directories_struct);

}

/**
 * find_fname - It looks for existence and permissions of the binary.
 * @command: Current command.
 *
 * Return: It returns 0 on success, otherwise returns 1.
 */

int find_fname(char *command)
{
	dir *directories = NULL, *tmp;
	struct stat st;

	if ((command[0] != '.' && command[1] != '/'))
	{
		if ((command[0] != '/'))
		{
			directories = path_helper();

			while (directories)
			{
				_strcat(directories->directory, "/");
				_strcat(directories->directory, command);
				if ((stat(directories->directory, &st)) == 0)
				{
					if (!access(directories->directory, X_OK) && (st.st_mode & __S_IFREG))
					{
						free_linked(directories);
						return (0);
					}
					else
					{
						free_linked(directories);
						return (126);
					}
				}
				tmp = directories->next;
				free(directories->directory);
				free(directories);
				directories = tmp;
			}
		}
	}
	return (127);
}

/**
 * exe_fname - It executes the given command via binary name.
 * @av: Array of arguments with the current command.
 *
 * Return: It returns 0 on success, otherwise returns 1.
 */

int exe_fname(char **av)
{
	dir *directories = NULL, *tmp;

	directories = path_helper();

	while (directories)
	{
		_strcat(directories->directory, "/");
		_strcat(directories->directory, av[0]);
		if (execve(directories->directory, av, environ) < 0)
		{
			tmp = directories->next;
			free(directories->directory);
			free(directories);
			directories = tmp;
			continue;
		}
	}

	free_linked(directories);
	return (127);
}
