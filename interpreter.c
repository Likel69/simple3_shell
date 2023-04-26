#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROMPT "$ "

/**
 * main - Entry point for the shell
 *
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while (1)
    {
        printf(PROMPT);
        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            putchar('\n');
            break;
        }
        line[read - 1] = '\0'; /* remove newline character */

        pid_t pid = fork();
        if (pid == -1)
        {
            perror("Error");
            return (1);
        }
        else if (pid == 0) /* child process */
        {
            if (execve(line, NULL, NULL) == -1)
            {
                perror("Error");
                return (1);
            }
        }
        else /* parent process */
        {
            wait(NULL);
        }
    }

    free(line);
    return (0);
}
