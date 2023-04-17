#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - fork & wait example
 *
 * Return: Always 0.
 *
 * RETURN VALUE:
 * wait():  on success, returns the process ID of the terminated child;
 * on error, -1 is returned.
 *
 * waitpid(): on success, returns the process ID of the child whose  state
 * has changed; if WNOHANG was specified and one or more child(ren) speci‐
 * fied by pid exist, but have not yet changed state, then 0 is  returned.
 * On error, -1 is returned.
 *
 * waitid():  returns  0  on  success  or  if WNOHANG was specified and no
 * child(ren) specified by id has yet changed state; on error, -1  is  re‐
 * turned.
 *
 * Each  of  these calls sets errno to an appropriate value in the case of
 * an error.
 */

int main(void)
{
	pid_t child_pid;
	int status;
	
	child_pid = fork();
	
	if (child_pid == -1)
	{
		perror("Error:");
		return(1);
	}
	
	if (child_pid == 0)
	{
		printf("wait for me, wait for me\n");
		sleep(10);
	}
	else
	{
		wait(&status);
		printf("Oh, it's all better now\n");
		printf("child pid is %u \n", child_pid);
	}
	
	return (0);
}

