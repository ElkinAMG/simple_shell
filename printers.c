#include "shell.h"

/**
 * _perror - It's a error showed to stdout.
 * @sname: Current shell name.
 * @cmd: Current command.
 * @msg: Error message to print.
 * @counter: The current value of given commands.
 *
 * Return: It returns nothing.
 */

void _perror(char *sname, char *cmd, char *msg, int counter)
{

	_puts(sname);
	_puts(": ");
	print_integer(counter);
	_puts(": ");
	_puts(cmd);
	_puts(": ");
	_puts(msg);

}

/**
 * _puts - It prints a string.
 * @str: String to be printed.
 *
 * Return: It returns nothing.
 */

void _puts(char *str)
{

	for (; *str; str++)
		write(STDERR_FILENO, str, 1);

}

/**
 * print_integer - Prints integer values.
 * @integer: integer to print.
 *
 * Return: Return integer numbers.
 */

void print_integer(int integer)
{
	int iter;
	char *str = NULL;

	iter = 0;

	str = _calloc(21, sizeof(char));

	if (integer == 0)
		*(str + iter) = '0';

	while (integer > 0)
	{
		*(str + iter) = ((integer % 10) + '0'), iter++;
		integer /= 10;
	}

	_reverse(str);

	*(str + iter) = '\0';

	_puts(str);

	free(str);
}


/**
 * _reverse - Reverse a string (ItoA function).
 * @str: String to reverse.
 *
 * Return: Nothing
 */

void _reverse(char *str)
{
	char *start, *end, tmp;
	int i, j;

	for (i = 0; *(str + i); i++)
		;

	start = str;
	end = str;

	for (j = 0; j < (i - 1); j++)
		end++;

	for (j = 0; j < (i / 2); j++)
	{
		tmp = *start;
		*start = *end;
		*end = tmp;

		start++;
		end--;
	}
}
