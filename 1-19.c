#include <stdio.h>
#define MAXLINE 1000

int getline(char line[], int maxline);
void reverse(char s[]);

/* print longest input line */
main()
{
    char line[MAXLINE];
    int len;

	while ( (len = getline(line, MAXLINE)) > 0) {
	    if (len > 0){	/* there was a line */
	        reverse(line);
		    printf("%s", line);
	    }
	}
	return 0;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i )
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
	int i;
	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}

void reverse(char s[])
/* reverse a string in place*/
{
    int c, i, j;
	for (i = 0; (c = s[i]) != '\n'; ++i ){}
	/*printf("Length: %d\n", i); */
    for (j = 0; (j < i/2); ++j){
        c = s[i-1-j];
        /* printf("j,c: %d, %c\n", j, c); */
        s[i-1-j] = s[j];
        s[j] = c;
    }
}