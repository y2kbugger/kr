#include <stdio.h>
#define MAXLINE 1000

int getline(char line[], int maxline);
void copy(char to[], char from[]);
void strip(char s[]);

/* print longest input line */
main()
{
    char line[MAXLINE];
    int len;

	while ( (len = getline(line, MAXLINE)) > 0) {
	    if (len > 0){	/* there was a line */
	        strip(line);
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

void strip(char s[])
/* strip trailing tabs and spaces */
{
    int c, i, j;
	for (i = 0; (c = s[i]) != '\0'; ++i ){
	}
    for (j = i-2; (j > 0 && ((c = s[j]) == ' ' || c == '\t')); --j ){}
    if (j < 0){
        s[0] = '\0';   
    } else{
	    s[j + 1] = '\n';
	    s[j + 2] = '\0';
    }
	

}