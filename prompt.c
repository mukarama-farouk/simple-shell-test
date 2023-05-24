#include "shell.h"

/**
 * prompt - function to print the prompt
 *
 * Return: Nothing
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "hsh>> ", 6);
}


/**
 * doornob - function to handle Ctr + C
 * @signal_song: The signal to handle
 *
 * Return: Nothing
 */
void doornob(int signal_song)
{
	(void)signal_song;
	write(STDOUT_FILENO, "\nhsh>> ", 7);
}


/**
 * _EOF - function to check if buffer is EOF
 * @buffer: pointer to input string
 *
 * Return: Nothing
 */
void _EOF(char *buffer)
{
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);
	free(buffer);
	exit(EXIT_SUCCESS);
}


/**
 * shell_ex - function to exit the shell
 * @cmd: pointer to token command
 *
 * Return: Nothing
 */
void shell_ex(char **cmd)
{
	int sta_tus = 0;

	if (cmd[1] == NULL)
	{
		free_donut(cmd);
		exit(EXIT_SUCCESS);
	}

	sta_tus = _atoi(cmd[1]);
	free_donut(cmd);
	exit(sta_tus);
}
