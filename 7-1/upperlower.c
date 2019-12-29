/* Exercise 7-1. Write a program that converts upper case to lower or lower
 * case to upper, depending on the name it is invoked with, as found in
 * argv[0]. */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void upper();
void lower();

int main(int argc, char **argv)
{
    int (*casechange)(int d);

    /* could be slightly more general detecting argv[0] */
    if (strcmp(*argv, "./upper") == 0)
        casechange = &toupper;
    else if (strcmp(*argv, "./lower") == 0)
        casechange = &tolower;
    else
        printf("%s",
               "executable name should be either './upper' or './lower'\n");

    int c;
    while ((c = getchar()) != EOF)
        putchar(casechange(c));
}
