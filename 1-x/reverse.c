#include <stdio.h>

main()
{
	int c, d;
	
	printf("eof: %d\n", EOF);
	while (((c = getchar()) != EOF ) && ((d = getchar()) != EOF))
	    {
	        if (c == '\n')
	            {
	                putchar(c);
	            }
	        else if (d == '\n')
	            {
	                putchar(c);
	                putchar(d);
	            }
	        else
	            {
	                putchar(d);
	                putchar(c);
	            }
 	    }
}