#include "shell.h"

/**
 * cmd_execute - Executes the commands
 * @cmdLine: Command line
 * @envp: Environment variable
 *
 * Return: no return
 */
void cmd_execute(char *cmdLine, char *envp[])
{
	char *args[6];

	get_token(cmdLine, args);

	int child_status;

	if (my_strcmp(args[0], "exit") == 0)
		shell_exit();
	else if (my_strcmp(args[0], "/bin/ls") == 0)
		execve(args[0], args, envp);
	else if (my_strcmp(args[0], "env") == 0)
		print_env();
	else
	{
		pid_t child_pid = fork();

		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		} else if (child_pid == 0)
		{
			get_path(args[0], args, envp);

			perror("execve");
			exit(EXIT_FAILURE);
		} else
			waitpid(child_pid, &child_status, 0);
	}
}



