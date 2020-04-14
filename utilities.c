#include "shell.h"

/**
 * add_node_end - Add new node at the end of a linked list.
 * @head: Reference to the header of a LL.
 * @s: String.
 *
 * Return: Node Address.
 */

dir *add_node_end(dir **head, char *s)
{

	dir *newNode;

	if (!head || !s)
		return (NULL);

	newNode = malloc(sizeof(dir));
	if (!newNode)
		return (NULL);

	newNode->directory = _strdup(s);
	newNode->next = NULL;

	while (*head)
		head = &(*head)->next;

	*head = newNode;

	return (newNode);
}

/**
 * _calloc - It allocates memory for an array, using malloc.
 * @nmemb: Array with elements.
 * @size: Size of array with elements.
 *
 * Return: It returns  a pointer to the allocated memory.
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	unsigned int i, j;
	char *ar;

	if (nmemb == 0 || size == 0)
		return (NULL);

	i = (nmemb * size);

	ar = malloc(sizeof(char) * i);
	if (ar == NULL)
		return (NULL);

	for (j = 0; j < i; j++)
		*(ar + j) = 0;

	return (ar);
}

/**
 * _getenv - It gets a wanted environment variable.
 * @var: Environment variable wanted.
 *
 * Return: It returns a pointer to a char with the variable wanted.
 */

char *_getenv(char *var)
{

	int i, j, k;
	int flag = 0;
	char *str = NULL;
	int len;

	if (var)
	{
		len = _strlen(var);
		for (i = 0; environ[i]; i++)
		{
			if (flag == 1)
			{
				break;
			}
			for (j = 0; j < len; j++)
			{
				if (environ[i][j] == *(var + j)) /*Look for matches*/
				{
					if ((j + 1) == len)
					{
						flag = 1;
						break;
					}
				}
				else
				{
					break;
				}
			}

		}
		str = _calloc(sizeof(*str), (_strlen(environ[i - 1]) - len));
		if (!str)
			return (NULL);

		for (k = 0, j = (len + 1); environ[i - 1][j]; k++, j++)
			str[k] = environ[i - 1][j];
	}
	return (str);
}

/**
 * _memcpy - copies n bytes from src to dest
 * @dest: destination pointer
 * @src: source pointer
 * @n: number of bytes to copy
 *
 * Return: pointer to dest
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		*(dest + i) = *(src + i);

	return (dest);
}

/**
 * free_linked - Free all memory data allocated.
 * @head: Linked List.
 *
 * Return: It returns anything.
 */

void free_linked(dir *head)
{
	dir *temp;

	while (head)
	{
		temp = head->next;
		free(head->directory);
		free(head);
		head = temp;
	}
}
