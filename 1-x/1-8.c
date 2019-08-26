#include <stdio.h>
#include <unistd.h>

int main()
{
    int blank, tab, newline;
    blank = 0;
    tab = 0;
    newline = 0;

    int c;
    while( (c = getchar()) != EOF )
    {
        if(c == '\n')
            ++newline;
        if(c == ' ')
            ++blank;
        if(c == '\t')
            ++tab;
    }
    printf("newlines: %d\n", newline);
    printf("tabs: %d\n", tab);
    printf("blanks: %d\n", blank);
}
