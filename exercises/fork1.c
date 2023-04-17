#include <stdio.h>
#include <unistd.h>

/**
 * main - fork example
 *
 * Return: Always 0 (success).
 * fork returns 0 to the child and the PID of the child to the father.
 * this helps us know if the current process is the child or the father.
 */

int main(void)
{
	pid_t my_pid;
	pid_t child_pid;
	
	child_pid = fork();
	
	if (child_pid == -1)
	{
		perror("Error:");
		return(1);
	}
	
	my_pid = getpid();
	printf("My pid is %u\n", my_pid);
	
	if (child_pid == 0)
	{
		printf("(%u) Nooooooo!\n", my_pid);
	}
	else
	{
		printf("(%u) %u, I am your father\n", my_pid, child_pid);
		return (0);
	}
}

