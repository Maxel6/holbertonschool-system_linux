#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 256

int main (int argc, char *argv[]){
    DIR *dir;
    struct dirent *read;

    dir = opendir("..");
    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    while ((read = readdir(dir)) != NULL)
        printf("%s  ", read->d_name);

    closedir(dir);
    return 0;
}