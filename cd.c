#include "shell.h"

/**
 * create_door - function to create a sub process
 * @cmd: pointer to token command
 * @nm: pointer to name of shell
 * @env: pointer to the env variables
 * @cc: number of executed cicles
 *
 * Return: Nothing.
 */
void create_door(char **cmd, char *nm, char **env, int cc)
{
	int pid = 0;
	int status = 0;
	int wait_error = 0;

	pid = fork();
	if (pid < 0)
	{
		perror("Error: ");
		free_ex(cmd);
	}
	else if (pid == 0)
	{
		execute(cmd, nm, env, cc);
		free_donut(cmd);
	}
	else
	{
		wait_error = waitpid(pid, &status, 0);
		if (wait_error < 0)
		{
			free_ex(cmd);
		}
		free_donut(cmd);
	}
}


/**
  * change_direct - function to change working directory
  * @trail: current working directory
  *
  * Return: 0 on success, -1 on failure
  */
int change_direct(const char *trail)
{
	char *buffer = NULL;
	size_t size = 1024;

	if (trail == NULL)
		trail = getcwd(buffer, size);
	if (chdir(trail) == -1)
	{
		perror(trail);
		return (98);
	}
	return (1);
}
