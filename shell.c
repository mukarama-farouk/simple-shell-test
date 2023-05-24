#include "shell.h"

/**
 * main - function to run the shell
 * @acrg: number of arguments
 * @avrg: pointer to arguments
 * @env: pointer to env variables
 *
 * Return: Always 0
 */
int main(int acrg, char **avrg, char **env)
{
	char *buffer = NULL, **cmd = NULL;
	size_t buffer_size = 0;
	ssize_t chars_readed = 0;
	int cc = 0;
	(void)acrg;

	while (1)
	{
		cc++;
		prompt();
		signal(SIGINT, doornob);
		chars_readed = getline(&buffer, &buffer_size, stdin);
		if (chars_readed == EOF)
			_EOF(buffer);
		else if (*buffer == '\n')
			free(buffer);
		else
		{
			buffer[_strlen(buffer) - 1] = '\0';
			cmd = token(buffer, " \0");
			free(buffer);
			if (_strcmp(cmd[0], "exit") != 0)
				shell_ex(cmd);
			else if (_strcmp(cmd[0], "cd") != 0)
				change_direct(cmd[1]);
			else
				create_door(cmd, avrg[0], env, cc);
		}
		fflush(stdin);
		buffer = NULL, buffer_size = 0;
	}
	if (chars_readed == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}


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
