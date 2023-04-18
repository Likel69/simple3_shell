#include "main.h"

void exec(char **argv)
{
	char *command = NULL;
	
	if (argv)
	{
		/* obtain the command */
		command = argv[0];
		
		/* execute the command */
		if (execve(command, argv, NULL) == -1)
		{
			perror("Error:");
		}
	}
}
