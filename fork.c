#include <stdio.h>
#include <unistd.h>

/**
 * main - fork example
 *
 * Return: Always 0 (success).
 *
 * RETURN VALUE:
 * On success, the PID of the child process is returned in the parent, and
 * 0  is returned in the child.  On failure, -1 is returned in the parent,
 * no child process is created, and errno is set appropriately.
 */

int main(void)
{
	pid_t my_pid;
	pid_t pid;
	
	printf("Before fork\n");
	pid = fork();
	
	if (pid == -1)
	{
		perror("Error:");
		return (1);
	}
	
	printf("After fork\n");
	my_pid = getpid();
	printf("My pid is %u\n", my_pid);
	return(0);
}

