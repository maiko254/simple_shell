#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

#define TOK_BUFSIZE 1024
#define PRINT(c) (write(STDOUT_FILENO, c, _strlen(c)))
#define PROMPT "#cisfun# "

char *read_line(void);
char **split_line(char *line);
int shell_launch(char **args);
int _strlen(char *str);

#endif
