#include <stdio.h>
#define MAXLINE 500
#define THRESH 8

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/* print input lines hreater that 8 cha
r*/
main()
{
	int len;					/* current line length */
	char line[MAXLINE];			/* current line */
	while ((len = getline(line, MAXLINE)) > 0) {
		/* printf("%d", len); */
		if (len > THRESH) {
		    printf("%s", line);
		}
	}
		
	return 0;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
	int c, i;
	for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i )
	if (i < lim)
		s[i] = c;
	if (c == '\n') {
	    /* strip \n and immediately return */
		return i; 
	}
	s[i] = '\0';
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
	int i;
	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}