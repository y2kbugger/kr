#include <stdio.h>
#include <unistd.h>

int main()
{
    int c;
    while( (c = getchar()) != EOF )
    {
        if (c==' ')
        {
            putchar(c);
            while((c=getchar())==' ')
                ;
        }
    putchar(c);
    }
}
