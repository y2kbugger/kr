/* Exercise 6-6. Implement a simple version of the #define processor (i.e., no
 * arguments) suitable for use with C programs, based on the routines of this
 * section. You may also find getch and ungetch helpful. */

struct nlist {                  /* table entry: */
    struct nlist *next;         /* next entry in chain */
    char *name;                 /* defined name */
    char *defn;                 /* replacement text */
};

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /* pointer table */
struct nlist *install(char *name, char *defn);
struct nlist *lookup(char *);
void undef(char *name);
char *mystrdup(char *);
void lookup_and_print(char *name);
int check_line_for_preprocessor(char *line);
int check_line_for_define_replacement(char *line);
void install_definition();

int main()
{
    char *line = "";
    size_t linelen = 0;
    while (getline(&line, &linelen, stdin) > 0) {
        if (!check_preprocessor_line(line)) {
            printf("%s", line);
        }
    }
}

int check_line_for_preprocessor(char *line)
{
    char *definekw = "#define";
    char *definekw_ptr = definekw;

    /* rewrite with strncmp */
    for (char *l = line; *l != '\n'; l++) {
        if (*definekw_ptr == '\0') {
            install_definition(l);
            return 1;
        } else if (*definekw_ptr == *l) {
            /* keep going if we are matching the word we are looking for */
            definekw_ptr++;
        } else
            /* not actually a define */
            break;
    }
    return 0;
}

int check_line_for_define_replacement(char *line)
{
    char *l = line;
    while (isalnum(c)) {
        /* break up into words and perform lookups */
    }
}

#define DEFARGS_NAME_SIZE 100
void install_definition(char *defn_args)
{
    while (isspace(*defn_args) && (*defn_args != '\n'))
        defn_args++;

    char *name = malloc(sizeof(name[0]) * DEFARGS_NAME_SIZE);
    char *n = name;
    while (!isspace(*defn_args) && (*defn_args != '\n'))
        *n++ = *defn_args++;
    *n = '\0';

    while (isspace(*defn_args) && (*defn_args != '\n'))
        defn_args++;

    char *defn = malloc(sizeof(defn[0]) * DEFARGS_NAME_SIZE);
    char *d = defn;
    while (!isspace(*defn_args) && (*defn_args != '\n'))
        *d++ = *defn_args++;
    *d = '\0';

    /* ignore the rest of the line */
    while (*defn_args != '\n')
        defn_args++;

    install(name, defn);
    free((void *) name);
    free((void *) defn);
}

void lookup_and_print(char *name)
{
    struct nlist *nlist;
    nlist = lookup(name);
    if (nlist != NULL)
        printf("`%s` ==> `%s`\n", name, nlist->defn);
    else
        printf("`%s` Not Found\n", name);

}

/* hash:  form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* lookup:  look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;          /* found */
    return NULL;                /* not found */
}

/* undef:  remove name from hashtab */
void undef(char *name)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {  /* not found */
        printf("Could not undef `%s` not found\n", name);
    } else {                    /* already there */
        hashval = hash(name);
        hashtab[hashval] = np->next;
        free((void *) np->defn);        /* free previous defn */
        free((void *) np);      /* free previous np */
    }

    printf("Removed `%s`\n", name);
}

/* install:  put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {  /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else                      /* already there */
        free((void *) np->defn);        /* free previous defn */
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;

    printf("/* Installed `%s` ==> `%s` */\n", name, defn);
    return np;
}

char *mystrdup(char *s)
{                               /* make a duplicate of s */
    char *p;

    p = (char *) malloc(strlen(s) + 1); /* +1 for '\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
}























/* d */
/* d */
/* d */
/* d */
/* d */
