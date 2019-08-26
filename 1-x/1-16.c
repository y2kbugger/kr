#include <stdio.h>
#define MAXLINE 5

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
main()
{
	int len;					/* current line length */
	int max;					/* maximum length so far */
	char line[MAXLINE];			/* current line */
	char longest[MAXLINE];		/* longest line */

	max = 0;
	while ((len = getline(line, MAXLINE)) > 0) {
		/* printf("%d", len); */
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	}
	if (max > 0)				/* there was a line */
		printf("%s", longest);
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