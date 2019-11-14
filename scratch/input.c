#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
 * Want to process args without using argc
 */

int main(int argc, char **argv)
{
    while (*argv)
        printf("%s\n", *argv++);
}
