#include "shell.h"

/**
 * free_donut - function to free memory allocated for command
 * @cmd: pointer to allocated memory
 *
 * Return: Nothing
 */
void free_donut(char **cmd)
{
	size_t n = 0;

	if (cmd == NULL)
		return;

	while (cmd[n])
	{
		free(cmd[n]);
		n++;
	}

	if (cmd[n] == NULL)
		free(cmd[n]);
	free(cmd);
}


/**
 * free_ex - function to free memory allocated and exit
 * @cmd: pointer to allocated command memory
 *
 * Return: Nothing
 */
void free_ex(char **cmd)
{
	size_t n = 0;

	if (cmd == NULL)
		return;

	while (cmd[n])
	{
		free(cmd[n]);
		n++;
	}

	if (cmd[n] == NULL)
		free(cmd[n]);
	free(cmd);
	exit(EXIT_FAILURE);
}
