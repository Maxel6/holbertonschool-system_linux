#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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
    char *dir_name = ".";
    if (argc <= 2)
    {
        if (argc == 2)
        {
            dir_name = argv[1];
        }
        dir = opendir(dir_name);
        if (errno == EPERM)
        {
            fprintf(stderr, "%s: cannot open %s: ", argv[0], dir_name);
            perror("");
            exit(EXIT_FAILURE);
        }
        if (errno == ENOENT)
        {
            fprintf(stderr, "%s: cannot access %s: ", argv[0], dir_name);
            perror("");
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
    }
    else
    {
        for (i = 1; i < argc; i++)
        {
            dir_name = argv[i];

            dir = opendir(dir_name);
            if (errno == EPERM)
            {
                fprintf(stderr, "%s: cannot open %s: ", argv[0], dir_name);
                perror("");
                exit(EXIT_FAILURE);
            }
            if (errno == ENOENT)
            {
                fprintf(stderr, "%s: cannot access %s: ", argv[0], dir_name);
                perror("");

                exit(EXIT_FAILURE);
            }
            printf("%s:\n", dir_name);
            while ((read = readdir(dir)) != NULL)
            {
                if (_strcmp(read->d_name, ".") != 0 && _strcmp(read->d_name, "..") != 0 && read->d_name[0] != '.')
                {
                    printf("%s  ", read->d_name);
                }
            }
            printf("\n\n");

            closedir(dir);
        }
    }
    return (0);
}
