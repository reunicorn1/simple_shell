#include <errno.h>
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
 *
 * Return: -1 in failure only
 */

int execute(char **arg, char *cmd)
{
	int stat;

	stat = execve(cmd, arg, environ);
	if (stat == -1)
		perror("Error: execution failed\n");
	return (stat);
}

/**
 * comand_runner - check for built in functions and execute commands
 * @arg: is the array of pointers composing the tokens
 * @input_string: contains the raw user input
 * @count: the number of argument which are processed until now
 * @error: pointer to the error code passed by loop
 * @prog_name: a name by which the shell is run
 *
 * Return: the status of the execution and (-1) on faliure
 */

int command_runner(char **arg, char *input_string,
		int count, int *error, char **prog_name)
{
	char **cmd_array = NULL, *cmd = NULL;
	pid_t child_pid = 0;
	int status = 0, stat = 0;

	cmd_array = cmd_list(arg);
	while (cmd_array)
	{
		cmd = checkpoint(cmd_array, input_string, count);
		if (cmd == NULL) /*we couldn't find the path*/
		{
			*error = 127;
			/*fprintf(stderr, "%s: ", *prog_name);*/
			/*perror("");*/
			fprintf(stderr, "%s: %d: %s: not found\n",
					*prog_name, count, cmd_array[0]);
		}
		if (cmd && (is_builin(cmd) != 0))
		{
			child_pid = fork();
			if (child_pid == -1)
			{
				perror("Error: fork failed\n");
				return (-1);
			}
			if (child_pid == 0)
			status = execute(cmd_array, cmd);
			else
			{
				waitpid(child_pid, &stat, 0);
				*error = WEXITSTATUS(stat);
				if (!(cmd_array[0][0] == '/' || cmd_array[0][0] == '.'))
					free(cmd);
			}
		}
		cmd_array = cmd_list(arg);
	}
	return (status);
}

/**
 * loop - the real engine beind how simple shell work
 * @prog_name: the name by which the program is run
 *
 * Return: Nothing.
 */

void loop(char **prog_name)
{
	char *input_str;
	char **arg;
	int count = 0;
	int status = 0, error = 0;

	while (1)
	{
		error_stat(error);
		if (!(isatty(STDIN_FILENO)))
		{
			if (is_input_eof())
				exit(error);
		}
		else
			write(1, "($) ", 4); /* to be changed later */
		count++;  /*to keep track of number of loops*/
		input_str = recieve_input(); /* getline in the hood */
		arg = toker(input_str); /* tokonize the input */
		if (arg[0] != NULL)
		{
			status = command_runner(arg, input_str, count, &error, prog_name);
		}
		if (status != -1) /*return here to review this condition*/
		{
			/* freeing memory */
			free(input_str);
			free(arg);
		}
	} /* edited the do while loop into one while loop */
}

/**
 * main - Entry point
 * @ac: the arguments count
 * @av: the argument vector
 *
 * Return: Nothing.
 */

int main(int ac __attribute__((unused)), char **av)
{
	loop(&av[0]);
	return (0);
}
