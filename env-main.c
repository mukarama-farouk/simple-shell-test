#include "shell.h"

/**
 * execute - function to execute a command
 * @cmd: pointer to token command
 * @nm: name of shell
 * @env: pointer to env variables
 * @cc: number of executed cicles
 *
 * Return: Nothing
 */
void execute(char **cmd, char *nm, char **env, int cc)
{
	char **pathways = NULL, *full_path = NULL;
	struct stat st;
	unsigned int i = 0;

	if (_strcmp(cmd[0], "env") != 0)
		print_env(env);
	if (stat(cmd[0], &st) == 0)
	{
		if (execve(cmd[0], cmd, env) < 0)
		{
			perror(nm);
			free_ex(cmd);
		}
	}
	else
	{
		pathways = _getTRAIL(env);
		while (pathways[i])
		{
			full_path = _strcat(pathways[i], cmd[0]);
			i++;
			if (stat(full_path, &st) == 0)
			{
				if (execve(full_path, cmd, env) < 0)
				{
					perror(nm);
					free_donut(pathways);
					free_ex(cmd);
				}
				return;
			}
		}
		error_msg(nm, cc, cmd);
		free_donut(pathways);
	}
}


/**
 * print_env - function to print all env variables
 * @env: pointer to env variables
 *
 * Return: Nothing
 */
void print_env(char **env)
{
	size_t n = 0, len = 0;

	while (env[n])
	{
		len = _strlen(env[n]);
		write(STDOUT_FILENO, env[n], len);
		write(STDOUT_FILENO, "\n", 1);
		n++;
	}
}


/**
 * _getTRAIL - function to get the full value
 * @env: pointer to env variables
 *
 * Return: All tokenized pathways for commands.
 */
char **_getTRAIL(char **env)
{
	char *pathvalue = NULL, **pathways = NULL;
	unsigned int n = 0;

	pathvalue = strtok(env[n], "=");
	while (env[n])
	{
		if (_strcmp(pathvalue, "PATH"))
		{
			pathvalue = strtok(NULL, "\n");
			pathways = token(pathvalue, ":");
			return (pathways);
		}
		n++;
		pathvalue = strtok(env[n], "=");
	}
	return (NULL);
}


/**
 * error_msg - function to print message not found
 * @nm: name of shell
 * @cc: number of cicles
 * @cmd: pointer to token command
 *
 * Return: Nothing
 */
void error_msg(char *nm, int cc, char **cmd)
{
	char c;

	c = cc + '0';
	write(STDOUT_FILENO, nm, _strlen(nm));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, &c, 1);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, cmd[0], _strlen(cmd[0]));
	write(STDOUT_FILENO, ": not found\n", 12);
}
