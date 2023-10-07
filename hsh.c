#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

extern char** environ;

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
	return (stat);
}

/**
 * loop - the real engine beind how simple shell work
 *
 * Return: Nothing.
 */

void loop(void)
{
	char *input_str;
	char **arg, *cmd;
	/*int count = 0;*/
	int status;
	pid_t child_pid;

	while (1)
	{
		/*count++;  to keep track of number of loops */
		/* taking user input */
		write(1, "UN!CORN-SHELL -> ", 18); /* to be changed later */
		input_str = recieve_input(); /* getline in the hood */
		/*printf("%s\n", input_str);*/
		if (!input_str)
		{
			write(1,"This is end of file\n", 20);
			exit(1); /* we terminate silently in EOF signal */
		}
		arg = toker(input_str); /* tokonize the input */
		if (arg[0] != NULL)
		{
			if (_strcmp(arg[0], "exit") == 0)
			{
				free(input_str);
				free(arg);
				exit(1);
			}
			cmd = checkpoint(arg);
			if (cmd == NULL) /*we couldn't find the path*/
				perror("./shell:"); /* we have to pass variable */
			else
			{
				child_pid = fork();
				if (child_pid == -1)
				{
					perror("Error: fork failed\n");
					return;
				}
				if (child_pid == 0)
				{
				status = execute(arg, cmd);
				if (status == -1)
					perror("Error: execution failed\n");
				}
				else
				{
					wait(NULL);
					if (arg[0][0] != '/')
						free(cmd);
				}
			}
		}
			if (status != -1)
			{
				/* freeing memory */
				free(input_str);
				free(arg);
				printf("I'm free\n");
			}
		
		
		
	} /* edited the do while loop into one while loop */
}
/**
 * main - Entry point
 *
 * Return: Nothing.
 */

int main(void)
{
	loop();

	return (0);
}
