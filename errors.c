#include "shell.h"

/**
 * _eputs - returns an input string
 * @str: the string to be printed
 *Return: will return nothing
 */
void _eputs(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_eputchar(str[j]);
		j++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: If successful 1.
 * If error, -1 is returned.
 */
int _eputchar(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}

/**
 * _putfd - will  write the character c to fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * If error, -1 is returned, and the error no, is altered.
 */
int _putfd(char c, int fd)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}

/**
 * _putsfd - a function that prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += _putfd(*str++, fd);
	}
	return (j);
}

