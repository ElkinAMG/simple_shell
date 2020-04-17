#include "shell.h"

/**
 * signalHandler - It handles the interruption signal.
 * @value: Set to ignore signals.
 * Return: It returns nothing.
 */

void signalHandler(int value)
{

	(void) value;

	signal(SIGINT, signalHandler);
	write(STDOUT_FILENO, "\n$ ", 3);
	fflush(stdout);

}

/**
 * main - It takes the job of execute the shell loop.
 * @ac: Arguments counter.
 * @av: Array of arguments.
 *
 * Return: It returns 0 on successful.
 */

int main(int ac, char **av)
{
	char *command = NULL;
	size_t size = 0;
	ssize_t bytes_read = 0;
	int flag = 0, ext = 0, counter = 1;

	signal(SIGINT, signalHandler);

	if (ac > 1)
	{
		free(command);
		return (0);
	}

	while (1)
	{
		if ((isatty(STDIN_FILENO)) == 1)
			write(STDOUT_FILENO, "$ ", 2);

		bytes_read = getline(&command, &size, stdin);
		if (bytes_read == EOF)
			break;

		fflush(stdout); /* Frees garbage from the buffer. */
		flag = recognize_command(command, ext, counter, av[0]);

		ext = flag;
		bytes_read = 0;
		counter++;
	}
	free(command);
	return (ext);
}
