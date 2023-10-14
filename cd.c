#include "main.h"

#include <unistd.h>
/**
 * _cd - change the current directory
 * @path: path to the new directory
 *
 * Return: 0 on success and -1 otherwise
 */

int _cd(char *path)
{
	int i;
	char *cwd = malloc(sizeof(char) * 512);

	if (cwd == NULL)
	{
		return (-1);
	}
	i = chdir(path);
	if (i == -1)
	{
		perror("shell");
		free(cwd);
		return (-1);
	}
	if (getcwd(cwd, 512) == NULL)
	{
		/*printf("%s\n", cwd);*/
		perror("getcwd failed:");
		free(cwd);
		return (-1);
	}
	else
	{
		setenv("PWD", cwd, 1);
		/*printf("env is set\n");*/
	}
	free(cwd);
	return (0);
}
