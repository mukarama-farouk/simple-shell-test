#include "shell.h"

/**
 * _strcmp - funtion to compare two strings
 * @str1: string 1
 * @str2: string 2
 *
 * Return: 1 if strings are the same, 0 if not
 */
int _strcmp(char *str1, char *str2)
{
	unsigned int i = 0;

	while (str1[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}

	return (1);
}


/**
 * _strlen - function to find the length of a string
 * @str: input string
 *
 * Return: The length of the string
 */
unsigned int _strlen(char *str)
{
	unsigned int len = 0;

	while (str[len])
		len++;

	return (len);
}


/**
 * _strcpy - function to copy a string to another string
 * @dest: pointer to copied string
 * @str: pointer to string to copy for
 *
 * Return: A pointer to copied string
 */
char *_strcpy(char *dest, char *str)
{
	char *zb1 = dest;

	while (*str)
		*dest++ = *str++;
	*dest = '\0';
	return (zb1);
}
