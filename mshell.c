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
		arr = word_list(lineptr, " ");

		if (stat(arr[0], &st) == 0)
		{
			child_pid = fork();
			if (child_pid == -1)
			{
				perror("Error:");
				exit(EXIT_FAILURE);
			}

			if (child_pid == 0)
			{
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
	free(arr);
	return (0);
}

/**
 * word_count - counts the number of words in a string tokenized using
 *              the strtok command
 * @str: string to tokenize
 * @delim: char to denote end of each string
 * Return: Number of strings returned by strtok
 */
size_t word_count(char *str, char *delim)
{
	size_t wc = 0;
	if (strtok(str, delim))
		++wc;
	while (strtok(NULL, delim) != NULL)
		++wc;
	return (wc);
}

/**
 * word_list - creates an array of pointers to strings returned by strtok
 *             and adding a null pointer at the end
 * @str: string to tokenize
 * @delim: char to denote end of each string
 * Return: pointer to an array of strings returned by strtok
 */
char **word_list(char *str, char *delim)
{
	char **arr, prev_char;
	size_t arr_size, arr_iter, str_iter, str_size;

	arr_size = 0;
	arr_iter = 0;
	str_size = strlen(str);
	prev_char = '\0';

	arr_size = word_count(str, delim);
	if (arr_size > 0)
	{
		arr = malloc(sizeof(char *) * (arr_size + 1));
		if (arr == NULL)
			exit(EXIT_FAILURE);
		for (str_iter = 0; str_iter < str_size; ++str_iter)
		{
			if (str[str_iter] != '\0' && prev_char == '\0')
			{
				arr[arr_iter] = str + str_iter;
				++arr_iter;
			}
			prev_char = str[str_iter];
		}
		arr[arr_iter] = NULL;
	}
	return (arr);
}
