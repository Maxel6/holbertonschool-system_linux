#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 256

/**
 * _strcmp - compare two strings
 * @s1: entry string 1
 * @s2: entry string 2
 * Return: the difference
 */
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
 * @argc: number of command-line arguments
 * @argv: array of command-line argument strings * Return: 0 on success
 * Return: 0 on succes
 */
int main(int argc, char *argv[])
{
	DIR *dir;
	struct dirent *read;
	int i = 0;

	for (i = 1; i < argc; i++)
	{
		dir = opendir(argv[i]);
		if (dir == NULL)
		{
			perror("Error opening directory");
			exit(EXIT_FAILURE);
		}
		printf("%s:\n", argv[i]);
		while ((read = readdir(dir)) != NULL)
		{
			if (_strcmp(read->d_name, ".") != 0 && _strcmp(read->d_name, "..") != 0
			&& read->d_name[0] != '.')
			{
				printf("%s  ", read->d_name);
			}
		}
		printf("\n");

		closedir(dir);
	}
	return (0);
}
