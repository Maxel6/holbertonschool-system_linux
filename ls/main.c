#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

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
int is_file(char *dir_name)
{
	struct stat sb;
	int res = 0;

	if (dir_name != NULL && (lstat(dir_name, &sb) != -1) && S_ISREG(sb.st_mode))
		res = 1;
	return (res);
}

int print_file(int argc, char ***argv)
{
	struct stat sb;
	int is_error = 0;
	int i = 0;

	for (i = 1; i < argc; i++)
	{
		if ((*argv)[i] != NULL && (lstat((*argv)[i], &sb) != -1) && S_ISREG(sb.st_mode))
		{
			printf("%s\n", (*argv)[i]);
		}
	}
	return (is_error);
}
int is_dir(char *dir_name)
{
	struct stat sb;
	int res = 0;

	if (dir_name != NULL && (lstat(dir_name, &sb) != -1) && S_ISDIR(sb.st_mode))
		res = 1;
	return (res);
}
int print_dir(int argc, char *program_name, char *dir_name)
{

	DIR *dir;
	struct dirent *read;
	int is_error = 0;

    if (dir_name == NULL)
    {
        return (-1);
    }
	dir = opendir(dir_name);
	if (errno == EACCES)
	{
		fprintf(stderr, "%s: cannot open directory %s: ", program_name, dir_name);
		perror("");
		is_error = 1;
	}
	else
	{
		if (argc > 2)
			printf("%s:\n", dir_name);
		while ((read = readdir(dir)) != NULL)
		{
			if (_strcmp(read->d_name, ".") != 0 && _strcmp(read->d_name, "..")
			!= 0 && read->d_name[0] != '.')
			{
				printf("%s  ", read->d_name);
			}
		}
		printf("\n");
	}
	closedir(dir);
	return (is_error);
}

int process_args(int argc, char ***argv)
{
	struct stat sb;
	int i = 0;
	int err = 0;
    
	for (i = 1; i < argc; i++)
	{
        if ((*argv)[i][0] == '-')
        {
            (*argv)[i] = NULL;
        }
		if (lstat((*argv)[i], &sb) == -1)
		{
            fprintf(stderr, "%s: cannot access %s: ", *argv[0], (*argv)[i]);
			perror("");
			(*argv)[i] = NULL;
			err = 1;
		}
	}

	return (err);
}

/**
 * main - entry point of the program
 * @argc: number of command-line arguments
 * @argv: array of command-line argument strings * Return: 0 on success
 * Return: 0 on succes
 */
int main(int argc, char *argv[])
{
	int i = 0;
	char *dir_name = ".";
	int is_error = 0;

	is_error += process_args(argc, &argv);
	if (argc <= 2)
	{
		if (argc == 2)
		{
			dir_name = argv[1];
		}

		if (is_dir(dir_name))
			is_error += print_dir(argc, argv[0], dir_name);
		if (is_file(dir_name))
		{
			printf("%s\n", dir_name);
		}
	}
	else
	{
		is_error += print_file(argc, &argv);
		for (i = 1; i < argc; i++)
		{
			dir_name = argv[i];
			if (dir_name)
			{
				if (is_dir(dir_name))
					is_error += print_dir(argc, argv[0], dir_name);
				printf("\n");
			}
		}
	}
	if (is_error != 0)
		exit(EXIT_FAILURE);
	return (0);
}
