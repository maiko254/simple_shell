#include "sh.h"

/**
 * main - reads the command line and executes the program or prints
 *        an error message if the executable cannot be found
 *
 * Return: Always 0
 */

int main(void)
{
	char *lineptr, **arr;
	size_t n;
	pid_t child_pid;
	int status, len;
	struct stat st;

	lineptr = NULL;
	n = 0;

	printf("#mshell$ ");
	while (getline(&lineptr, &n, stdin) != EOF)
	{
		len = strlen(lineptr);
		lineptr[len - 1] = '\0';

		if (stat(lineptr, &st) == 0)
		{
			child_pid = fork();
			if (child_pid == -1)
			{
				perror("Error:");
				exit(EXIT_FAILURE);
			}

			if (child_pid == 0)
			{
				arr = malloc(sizeof(char *) * 2);
				arr[0] = lineptr;
				arr[1] = NULL;
				execve(arr[0], arr, environ);
			}
			else
				wait(&status);
		}
		else
			printf("File Not Found\n");
		printf("#mshell$ ");
	}
	free(lineptr);
	return (0);
}
