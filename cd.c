#include "main.h"
#include <unistd.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <libgen.h>


/**
 * _cd - change the current directory
 * @path: path to the new directory
 *
 * Return: 0 on success and -1 otherwise
 */
int _cd(char *path)
{
	char *home = getenv("HOME");
	char *oldpwd = getenv("PWD");
	char *newpwd = NULL;
	int i = 0;

	if (path == NULL)
	{
		newpwd = home;
	}
	else if (_strcmp(path, "-") == 0)
	{
		if (oldpwd != NULL)
		{
			newpwd = oldpwd;
			i = 1;
		}
		else
		{
			fprintf(stderr, "OLDPWD not set\n");
			return (1);
		}
	}
	else
	{
		newpwd = path;
	}
	if (chdir(newpwd) == -1)
	{
		perror("chdir");
		return (1);
	}
	setenv("PWD", newpwd, 1);
	setenv("OLDPWD", oldpwd, 1);
	if (i == 1)
		print_pwd();
	return (0);
}

/**
  * print_pwd - run the pwd command
  *
  * Returns: nothing
 */

void print_pwd(void)
{
	pid_t child_pid;
	char *arr[] = {NULL};

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error: fork failed\n");
		return;
	}
	if (child_pid == 0)
		execve("/bin/pwd", arr, __environ);
	else
	{
		wait(NULL);
	}
}
