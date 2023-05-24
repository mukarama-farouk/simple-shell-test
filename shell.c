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
