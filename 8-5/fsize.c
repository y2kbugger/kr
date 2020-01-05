/* Exercise 8-5. Modify the fsize program to print the other information */
/* contained in the inode entry. */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>              /* flags for read and write */
#include <sys/types.h>          /* typedefs */
#include <sys/stat.h>           /* structure returned by stat */
#include "dirent.h"

void fsize(char *);

/* print file sizes */
int main(int argc, char **argv)
{
    if (argc == 1)              /* default: current directory */
        fsize(".");
    else
        while (--argc > 0)
            fsize(*++argv);
    return 0;
}

int stat(const char *, struct stat *);
void dirwalk(char *, void (*fcn)(char *));

/* fsize:  print size of file "name" */
void fsize(char *name)
{
    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
        dirwalk(name, fsize);
    printf("%16d %s\n", (int) stbuf.st_size, name);
}

#define MAX_PATH 1024

/* dirwalk:  apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *))
{
    char name[MAX_PATH];
    struct dirent *dp;
    DIR *dfd;

    if ((dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }
    while ((dp = readdir(dfd)) != NULL) {
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;           /* skip self and parent */
        if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s/%s too long\n",
                    dir, dp->d_name);
        else {
            sprintf(name, "%s/%s", dir, dp->d_name);
            (*fcn) (name);
        }
    }
    closedir(dfd);
}
