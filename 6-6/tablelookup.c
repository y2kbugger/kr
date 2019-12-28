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

#define HASHSIZE 1              /* Set to 1 to force collision to test undef reconnecting linked list */
static struct nlist *hashtab[HASHSIZE]; /* pointer table */
struct nlist *install(char *name, char *defn);
struct nlist *lookup(char *);
void undef(char *name);
char *mystrdup(char *);
void lookup_and_print(char *name);

int main()
{
    install("Hello", "Helllllllo");
    install("Goodbye", "weidersehen");
    install("Good", "Friends");
    install("Happy", "Life");
    install("Happy", "Wife");
    install("Spotted", "Dick");

    lookup_and_print("Hello");
    lookup_and_print("Hello");
    lookup_and_print("Hell");
    lookup_and_print("Goodbyee");
    lookup_and_print("Goodbye");
    undef("Hello");
    lookup_and_print("Hello");
    install("Hello", "Helllllllo");
    lookup_and_print("Hello");
    install("Hello", "Whats up???");
    lookup_and_print("Hello");
    undef("Hello");
    lookup_and_print("Hello");
    lookup_and_print("Spotted");
    return 0;
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

    printf("Installed `%s` ==> `%s`\n", name, defn);
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
