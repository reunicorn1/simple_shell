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
	char *newpwd, temp[PATH_MAX];
	int i = 0, s1 = 0, s2 = 0;

	if (path == NULL)
		newpwd = home;

	else if (_strcmp(path, "-") == 0)
	{
		if (oldpwd != NULL)
		{
			newpwd = getenv("OLDPWD");
			i = 1;
		}
		else
		{
			fprintf(stderr, "OLDPWD not set\n");
			return (1);
		}
	}
	else
		newpwd = realpath(path, temp);

	if (chdir(newpwd) == -1)
	{
		perror("chdir");
		return (1);
	}
	s1 = setenv("PWD", newpwd, 1);
	s2 = setenv("OLDPWD", oldpwd, 1);
	if (s2 == -1)
		fprintf(stderr, "error setting OLDPWD");
	if (s1 == -1)
		fprintf(stderr, "error setting OLDPWD");
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
		execve("/bin/pwd", arr, environ);
	else
	{
		wait(NULL);
	}
}
