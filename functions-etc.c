#include "shell.h"

/**
 * _strcat - function to concatenate two strings
 * @dest: input string
 * @str: input string
 *
 * Return: pointer to result string
 */
char *_strcat(char *dest, char *str)
{
	char *temp = dest;

	while (*dest)
		dest++;

	*dest++ = '/';
	while (*str)
		*dest++ = *str++;
	return (temp);
}


/**
 * _atoi - function to convert string to integer
 * @str: input string
 *
 * Return: integer from conversion
 */
int _atoi(char *str)
{
	int sign = 1;
	unsigned int t = 0;
	char null_flag = 0;

	if (str == NULL)
		return (0);
	while (*str)
	{
		if (*str == '-')
			sign *= -1;
		if (*str >= '0' && *str <= '9')
		{
			null_flag = 1;
			t = t * 10 + (*str - '0');
		}
		else if (*str < '0' || *str > '9')
		{
			if (null_flag == 1)
				break;
		}
		str++;
	}
	if (sign < 0)
		t = (-1 * (t));
	return (t);
}
