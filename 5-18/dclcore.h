#ifndef DCLCORE_H
#define DCLCORE_H

#define  MAXTOKEN  100
enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);
int gettoken(void);

int gettoken(void);
int tokentype;                  /* type of last token */
char token[MAXTOKEN];           /* last token string */
char name[MAXTOKEN];            /* identifier name */
char datatype[MAXTOKEN];        /* data type = char, int, etc. */
char out[1000];                 /* output string */


int getch(void);

void ungetch(int c);

#endif                          /* DCLCORE_H */
