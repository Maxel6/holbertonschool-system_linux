#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 256
/**
 * main - entry point of the program
 * Return: 0 on success
 */
int main(void)
{
	DIR *dir;
	struct dirent *read;

	dir = opendir("..");
	if (dir == NULL)
	{
		perror("Error opening directory");
		exit(EXIT_FAILURE);
	}

	while ((read = readdir(dir)) != NULL)
	{
		if (strcmp(read->d_name, ".") != 0 && strcmp(read->d_name, "..") != 0)
		{
			printf("%s\n", read->d_name);
		}
	}
	closedir(dir);
	return (0);
}
