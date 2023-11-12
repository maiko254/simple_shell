#ifndef SH_H
#define SH_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

size_t word_count(char *str, char *delim);
char **word_list(char *str, char *delim);

#endif
