#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - (fork + wait + execve) exercise
 *
 * Description: program that executes the command ls -l /tmp in 5 different child processes.
 * Each child should be created by the same parent process (the father).
 * Wait for a child to exit before creating a new child.
 * Return: Always 0 (success).
 */

int main(void)
{
	char *argv[] = {"/bin/ls", "-l", "/tmp/", NULL};
	char *envp[] = { NULL };
	
	pid_t my_pid;
	my_pid = getpid();/* get father's pid */
	
	pid_t child_pid;
	
	int status, i;
	
	for (i = 1; i <=5 ; i++)
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error:");
			return(1);
		}
		
		else if (child_pid == 0)
		{
			/*printf("wait for me \n");*/
			sleep(3);
		}
		else
		{
			wait(&status);
			printf("the father's pid is %u, while child_%d pid is %u \n", my_pid, i, child_pid);
			
			if (execve(argv[0], argv, envp) == -1)
			{
				perror("Error:");
			}	
		}
	}
		
	return (0);
}

