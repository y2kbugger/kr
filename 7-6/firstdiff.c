/* Exercise 7-6. Write a program to compare two files, printing the first line
 * where they differ. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* getting this from argv is left as exercise; */
char FILE1[] = "./file1.txt";
char FILE2[] = "./file2.txt";

int main()
{
    FILE *fp1;
    FILE *fp2;
    char *line1;
    char *line2;
    int getlinestatus1;
    int getlinestatus2;

    size_t len1;
    size_t len2;

    if ((fp1 = fopen(FILE1, "r")) == NULL)
        exit(1);
    if ((fp2 = fopen(FILE2, "r")) == NULL)
        exit(2);

    while (1) {
        getlinestatus1 = getline(&line1, &len1, fp1);
        getlinestatus2 = getline(&line2, &len2, fp2);
        if (getlinestatus1 < 0)
            break;
        if (getlinestatus2 < 0)
            break;
        if (strcmp(line1, line2) != 0) {
            printf("1:%s2:%s", line1, line2);
            break;
        }
    }
    exit(0);
}
