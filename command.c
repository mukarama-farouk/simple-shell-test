#include "shell.h"

/**
 * get_token - Tokenises the command line into command and
 * arguments
 * @cmdLine: Command line inputed
 * @args: Arguments to be passed
 *
 * Return: Null
 */
void get_token(char *cmdLine, char *args[])
{
	char *token;
	int argcount;

	token = strtok(cmdLine, " ");
	argcount = 0;

	while (token != NULL)
	{
		args[argcount] = token;
		argcount++;
		token = strtok(NULL, " ");
	}
	args[argcount] = NULL;
}


/**
 * void shell_exit - Exits the shell
 *
 * Return: no return
 */
void shell_exit(void)
{
	exit(0);
}


/**
 * get_path - searches for the command in each directory
 * in the PATH variable
 * @cmd: command
 * @envp: Environment variable
 *
 * Return: no return
 */
void get_path(char *cmd, char *args[], char *envp[])
{
	char *path = getenv("PATH");
	char *path_dir[12];
	int i;
	int dir_count = 0;
	char *dir;

	dir = strtok(path, ":");

	while (dir != NULL)
	{
		path_dir[dir_count] = dir;
		dir_count++;
		dir = strtok(NULL, ":");
	}

	for (i = 0; i < dir_count; i++)
	{
		char fullPath[450];

		sprintf(fullPath, "%s/%s", path_dir[i], cmd);

		if (access(fullPath, X_OK == 0))
			execve(fullPath, args, envp);
	}
}


/**
 * print_env - prints the env variables of the current director
 *
 * Return: no return
 */
void print_env(void)
{
	char **_env = environ;

	while (*_env != NULL)
	{
		size_t len = my_strlen(*_env);

		write(STDOUT_FILENO, *_env, len);
		write(STDOUT_FILENO, "\n", 1);
		_env++;
	}
}
