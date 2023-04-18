#include "shell.h"

/**
 **_strncpy - func will copy a string data struct
 *@dest is the destination string to be copy
 *@src: the source str
 *@n: no. of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int t, j;
	char *s = dest;

	t = 0;
	while (src[t] != '\0' && t < n - 1)
	{
		dest[t] = src[t];
		t++;
	}
	if (t < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - intended to concatenate the strings
 *@dest: the first string
 *@src: the second string
 *@n: maximum amnt of bytes
 *Return: string that has been concatenated
 */
char *_strncat(char *dest, char *src, int n)
{
	int t, j;
	char *s = dest;

	t = 0;
	j = 0;
	while (dest[t] != '\0')
		t++;
	while (src[j] != '\0' && j < n)
	{
		dest[t] = src[j];
		t++;
		j++;
	}
	if (j < n)
		dest[t] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@s: parsed string
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

