#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * main - simple shell
 *
 * Description: Unix command line interpreter.
 * Return: Always 0 (success).
 */

int main(void)
{
	char *command = NULL;
	size_t len = 0;
	ssize_t num_chars_read;
	char *envp[] = { NULL };
	char **argv = { NULL };
		
	while (1)
	{
		printf("$ ");
		
		num_chars_read = getline(&command, &len, stdin);
		
		if (command == NULL)
		{
			perror("Error: ");
			return(-1);
		}
		
		if (num_chars_read == -1)
		{
			/*printf("Exiting .... \n");*/
			return(1);
		}
		
		//command = argv[0];
		if (execve(argv[0], argv, envp) == -1)
		{
			perror("Error");
		}
}
		
	free(command);
	return (0);
}

