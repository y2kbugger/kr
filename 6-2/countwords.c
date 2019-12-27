/* Exercise 6-2. Write a program that reads a C program and prints in
 * alphabetical order each group of variable names that are identical in the
 * first 6 characters, but different somewhere thereafter. Don’t count words
 * within strings and comments. Make 6 a parameter that can be set from the
 * command line.
 *
 * We need to avoid comments first.
 * Then detect "variable names" via declaration
 *
 * Question:
 *  Do we group them in data structure, or only as we print them?
 * A:
 *  I think we can store them all and separate into groups while printing
 *
 * What do they mean by "groups?" what about printed like:
 *
 *   hello
 *
 *   goodbye
 *   goodbyeworld
 *
 *   zebrafoot
 *
 *
 */

#define MAXWORDLEN 100

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

struct WordNode {
    char *word;
    struct WordNode *left;
    struct WordNode *right;
};

char *get_word();
void insert_word(char *word, struct WordNode *treeroot);
void print_words(struct WordNode *rootnode);

/* Data for testing the printing program
 * Example of how it could be stored as tree:
 *
 *        goodbye
 *       /      \
 *   hello     goodbyeworld
 *                   \
 *                   zebrafoot
 */

struct WordNode testtree = {
    "goodbye",
    &(struct WordNode) { "hello", NULL, NULL },
    &(struct WordNode) { "goodbyeworld",
                        NULL,
                        &(struct WordNode) { "zebrafoot", NULL, NULL}
                         }
};

/* Command Line Settings */
int TEST = 0;

/* on by default for now, until we add arg handling */
int main()
{
    /* parse args */
    /* -t : print test words */
    /* -n : number of characters to consider a group */

    /* read in words from stdin */
    /* get pointer one word at a time, stored in dynamically allocated memory */

    struct WordNode tree = { NULL, NULL, NULL };
    char *word;
    while ((word = get_word()) != NULL)
        insert_word(word, &tree);

    /* print out the "variable names" in groups */
    printf("\n\nVariable names:\n");
    if (TEST)
        print_words(&testtree);
    else
        print_words(&tree);
    exit(0);
}

void print_words(struct WordNode *rootnode)
{
    if (rootnode->left != NULL)
        print_words(rootnode->left);
    if (rootnode->word != NULL)
        printf("%s\n", rootnode->word);
    if (rootnode->right != NULL)
        print_words(rootnode->right);
}

int keep_char(char c)
{
    if (isalpha(c))
        return 1;
    else
        return 0;
}

/* should only return words that are "variable names" (how to detect by context?) */
/* search tree for word, if not existing, store the word */
/* otherwise free the memory */
char *get_word()
{
    char c;
    char *word = malloc(MAXWORDLEN + 1);
    char *w = word;
    int charsleft = MAXWORDLEN;
    while ((c = getchar()) != EOF) {
        if (keep_char(c)) {
            *w++ = c;
            charsleft--;
        } else if (w > word) {
            /* finished with current word */
            break;
            /* else no word has been started yet */
        }
        if (!charsleft) {
            printf("Word exceeded MAXWORDLEN");
            break;
        }

    }
    *w = '\0';

    /* end of file, no word */
    if (word == w)
        return NULL;
    return word;
}

void insert_word(char *word, struct WordNode *treeroot)
{
    printf("*%s*", word);
}
