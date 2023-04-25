#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * main - shell project
 *
 * Description: Implementing my own Shell.
 * @ac: argument count
 * @argv: argument vector
 * Return: Always 0 (success).
 */

int main(int ac, char **argv)
{
	char *prompt = "#cisfun$ ";
	size_t n = 0;
	ssize_t num_chars_read; /* numbers of characters inputted into stdin */
	const char *delim = " \n";
	char *token;
	char *command = NULL;
	char *full_command = NULL;
	char *copy_command = NULL;
	int num_tokens = 0;
	int i;
	
	/* declaring void variables */
	(void)ac;

	/* creating an infinite loop */
	while (1)
	{
		printf("%s", prompt);
		num_chars_read = getline(&full_command, &n, stdin);
		
		/* Allocate memory to hold characters read by getline */
		copy_command = malloc(sizeof(char) * num_chars_read);
		
		if (copy_command == NULL)
		{
			perror("Error");
			return(-1);
		}
		
		/* make copy of the command entered into stdin */
		strcpy(copy_command, full_command);

		/* Check if getline function failed or reached EOF or user input Ctrl + D on stdin*/
		if(num_chars_read == -1)
		{
			printf("Exiting .....");
			return(-1);
		}
	
		/* split the string (full_command) into an array of words */
		token = strtok(full_command, delim);
	
		/* Calculate the total number of tokens */	
		while (token != NULL)
		{
			num_tokens++;
			token = strtok(NULL, delim);
		}
		num_tokens++;

		/* Allocate memory to hold array of strings */
		argv = malloc(sizeof(char *) * num_tokens);

		/* Store each token in the argv array */
		token = strtok(copy_command, delim);

		for (i =0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);
			
			// printf(">>>>> %s \n", argv[i]);
			token = strtok(NULL, delim);
		}
		argv[i] = NULL;
		
		/* execute the command */
		if (argv)
		{
			/* obtain the command */
			command = argv[0];
			
			/* execute the command */
			if (execve(command, argv, NULL) == -1)
			{
				perror("Error");
			}
		}
	}
	
	free(full_command);
	free(copy_command);
	return (0);
}

