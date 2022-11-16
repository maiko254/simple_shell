#ifndef MAIN_H
#define MAIN_H

#define TOK_BUFSIZE 1024

char *read_line(void);
char **split_line(char *line);
int shell_launch(char **args);

#endif
