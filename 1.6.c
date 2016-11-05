#include <stdio.h>

#define IN 1
#define OUT 0

int main()
{
    int c, i, nwhite, nother;
    int ndigit[10];

    nwhite = nother = 0;

    printf("eof: %d\n", EOF);
    for (i = 0; i < 10; ++i)
        ndigit[i] = 0;

    while ((c = getchar()) != EOF) {
        if (c >= '0' && c <= '9') {
            ++ndigit[c-'0'];
        }
        else if (c == ' ' || c == '\n' || c == '\t') {
            ++nwhite;
        }
        else {
            ++nother;
        }
    }
    for (i = 0; i < 10; ++i)
        printf("%d ", i);
    printf("\n");
    for (i = 0; i < 10; ++i)
        printf("%d ", ndigit[i]);
    printf("\nwhite: %d other: %d\n", nwhite, nother);
    return 0;
}
