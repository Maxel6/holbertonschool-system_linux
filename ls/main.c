#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 256

int _strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

/**
 * main - entry point of the program
 * Return: 0 on success
 */
int main(void)
{
	DIR *dir;
	struct dirent *read;

	dir = opendir(".");
	if (dir == NULL)
	{
		perror("Error opening directory");
		exit(EXIT_FAILURE);
	}

	while ((read = readdir(dir)) != NULL)
	{
		if (_strcmp(read->d_name, ".") != 0 && _strcmp(read->d_name, "..") != 0 && read->d_name[0] != '.')
		{
			printf("%s  ", read->d_name);
		}
	}
		printf("\n");

	closedir(dir);
	return (0);
}
