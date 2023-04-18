#include <stdio.h>

/**
 * main - Entry point
 *
 * Description: program that prints all the arguments without using ac
 * @ac: the total number of arguments given through the command line
 * @av: strings array
 * Return: Always 0 (success)
 */

int main(int ac, char **av)
{
	int all;

	for (all = 0; all < ac; ++all)
	{
		printf("string[%d]: %s\n", all, av[all]);
	}

	return (0);
}

