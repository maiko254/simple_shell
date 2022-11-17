#include "shell.h"

/**
 * _strlen - calculates length of a string
 * @str: given string
 *
 * Return: length of string or negative value on fail
 */
int _strlen(char *str)
{
	int len;

	for (len = 0; str[len]; len++)
		;

	return (len);
}
