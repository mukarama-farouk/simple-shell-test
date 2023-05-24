#include "shell.h"

/**
 * token - function to split and create full string command
 * @tmi: delimiter for strtok
 * @buffer: pointer to input string
 *
 * Return: string with full command
 */
char **token(char *buffer, const char *tmi)
{
	char *token = NULL, **cmds = NULL;
	size_t buffsize = 0;
	int i = 0;

	if (buffer == NULL)
		return (NULL);

	buffsize = _strlen(buffer);
	cmds = malloc((buffsize + 1) * sizeof(char *));
	if (cmds == NULL)
	{
		perror("Unable to allocate buffer");
		free(buffer);
		free_donut(cmds);
		exit(EXIT_FAILURE);
	}

	token = strtok(buffer, tmi);
	while (token != NULL)
	{
		cmds[i] = malloc(_strlen(token) + 1);
		if (cmds[i] == NULL)
		{
			perror("Unable to allocate buffer");
			free_donut(cmds);
			return (NULL);
		}
		_strcpy(cmds[i], token);
		token = strtok(NULL, tmi);
		i++;
	}
	cmds[i] = NULL;
	return (cmds);
}
