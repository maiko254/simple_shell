#include "shell.h"

/**
 * read_line - reads input from command line
 *
 * Return: buffer containing read line
 */
char *read_line(void)
{
	char *line = NULL;
	size_t buffsize = 0;

	if (isatty(STDIN_FILENO))
		PRINT(PROMPT);

	if (getline(&line, &buffsize, stdin) == -1)
	{
		if (feof(stdin))
			exit(EXIT_SUCCESS);
		else
		{
			perror("Error reading line");
			exit(EXIT_FAILURE);
		}
	}

	return (line);
}

/**
 * split_line - splits string into  sequence of non-empty tokens
 * @line: string to split
 *
 * Return: array containing split tokens, EXIT_FAILURE on failure
 */
char **split_line(char *line)
{
	int bufsize = TOK_BUFSIZE;
	int position = 0;
	char *token;
	char **tokens = malloc(sizeof(char) * bufsize);

	if (tokens == NULL)
	{
		perror("Allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		token = strtok(NULL, " \t\r\n\a");
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
 * shell_launch - creates child process and executes program
 * @args: array of arguments supplied to program
 *
 * Return: 1
 */
int shell_launch(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
			perror("./hsh");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		perror("Error forking");
	else
	{
		waitpid(pid, &status, WUNTRACED);
	}

	return (1);
}

/**
 * main - loop to execute programs
 *
 * Return: 0
 */
int main(void)
{
	char *line;
	char **args;
	int status;

	do {
		line = read_line();
		args = split_line(line);
		status = shell_launch(args);

		free(line);
		free(args);
	} while (status);

	return (0);
}
