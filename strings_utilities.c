#include "shell.h"

/**
 * _strlen - It gives the length of a given string.
 * @str: String to give length.
 *
 * Return: It returns the length of a given string.
 */

size_t _strlen(char *str)
{
	size_t len = 0;

	while (*(str + len) != '\0')
		len++;

	return (len);
}

/**
 * _strdup - Returns a pointer to a newly allocated space in memory.
 * @str: String to copy.
 *
 * Return: A copy of the string given as a parameter.
 */

char *_strdup(char *str)
{
	size_t i, j;
	char *newS;

	i = _strlen(str);

	newS = _calloc(1024, sizeof(char));
	if (!newS)
		return (NULL);

	j = 0;
	while (j < i)
		*(newS + j) = *(str + j), j++;

	return (newS);
}

/**
 * _strcat - Write a function that concatenates two strings.
 * @dest: destination
 * @src: source
 *
 * Return: two strings concatenates.
 */

char *_strcat(char *dest, char *src)
{
	int i, c;

	c = 0;

	while (*(dest + c) != '\0')
		c++;

	for (i = 0; src[i] != '\0'; i++)
		*(dest + c + i) = *(src + i);

	*(dest + c + i) = '\0';

	return (dest);
}

/**
 * _strcmp - compares two strings
 * @s1: string to compare
 * @s2: string to compare
 * Return: int
 */
int _strcmp(char *s1, char *s2)
{
	int x = 0;
	int y = 0;

	while ((s1[x] != '\0' && s2[y] != '\0') && s1[x] == s2[y])
	{
		s1++;
		s2++;
	}
	if (s1[x] == s2[y])
	{
		return (0);
	}
	else
	{
		return (s1[x] - s2[y]);
	}
}
