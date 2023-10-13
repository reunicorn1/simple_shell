#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"


/**
 * execute - execute the program required
 * @arg: the array of pointers which are the tokens
 * @cmd: the pathname
 * @_environ: a pointer of the array of environment variables
 *
 * Return: -1 in failure only
 */

int execute(char **arg, char *cmd, char ***_environ)
{
	int stat;

	stat = execve(cmd, arg, *_environ);
	if (stat == -1)
		perror("Error: execution failed\n");
	return (stat);
}

/**
 * loop - the real engine beind how simple shell work
 * @_environ: a pointer of the array of environment variables
 *
 * Return: Nothing.
 */

void loop(char ***_environ)
{
	char *input_str;
	char **arg, **cmd_array, *cmd;
	/*int count = 0;*/
	pid_t child_pid;
	int status;
	
	while (1)
	{
		if (!(isatty(STDIN_FILENO)))
		{
			if (is_input_eof())
				exit(0);
		}
		/*count++;  to keep track of number of loops*/
		/* taking user input */
		else
			write(1, "UN!CORN-SHELL -> ", 18); /* to be changed later */
		input_str = recieve_input(_environ); /* getline in the hood */
		/*printf("%s\n", input_str);*/
		arg = toker(input_str); /* tokonize the input */
		if (arg[0] != NULL)
		{
			cmd_array = cmd_list(arg);
			while (cmd_array)
			{
				cmd = checkpoint(cmd_array, input_str, _environ);
				if (cmd == NULL) /*we couldn't find the path*/
					perror("flag"); /* we have to pass variables */
				if (cmd && (is_builin(cmd) != 0))
				{
					child_pid = fork();
					if (child_pid == -1)
					{
						perror("Error: fork failed\n");
						return;
					}
					if (child_pid == 0)
						status = execute(cmd_array, cmd, _environ);
					else
					{
						wait(NULL);
						if (cmd_array[0][0] != '/')
							free(cmd);
					}
				}
				cmd_array = cmd_list(arg);
			}
		}
		if (status != -1) /*return here to review this condition*/
		{
			/* freeing memory */
			free(input_str);
			free(arg);
			/*printf("I'm free\n");*/
		}
	} /* edited the do while loop into one while loop */
}

/**
 * main - Entry point
 * @ac: the arguments count
 * av: the argument vector
 * @env: the environment pointer
 *
 * Return: Nothing.
 */

int main(int ac __attribute__((unused)),
		char **av __attribute__((unused)), char **env)
{
	char **_environ;
	int i, count = 0;

	while (env[count] != NULL)
		count++;
	_environ = malloc((count + 1) * sizeof(char*));
	for (i = 0; env[i] != NULL; i++)
	{
		_environ[i] = _strdup(env[i]);
		if (_environ[i] == NULL)
			return (-1);
	}
	_environ[i] = NULL;
	loop(&_environ);
	return (0);
}
