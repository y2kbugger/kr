/* Exercise 6-5. Write a function undef that will remove a name and definition
 * from the table maintained by lookup and install. */

struct nlist {                  /* table entry: */
    struct nlist *next;         /* next entry in chain */
    char *name;                 /* defined name */
    char *defn;                 /* replacement text */
};

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /* pointer table */
struct nlist *install(char *name, char *defn);
struct nlist *lookup(char *);
char *mystrdup(char *);
void lookup_and_print(char *name);

int main()
{
    install("Hello", "Helllllllo");
    install("Goodbye", "weidersehen");

    lookup_and_print("Hello");
    lookup_and_print("Hello");
    lookup_and_print("Hell");
    return 0;
}

void lookup_and_print(char *name)
{
    struct nlist *nlist;
    nlist = lookup(name);
    if (nlist != NULL)
        printf("`%s` ==> `%s`\n", name, nlist->defn);
    else
        printf("`%s` Not Found", name);

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
