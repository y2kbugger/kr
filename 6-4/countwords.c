/* Exercise 6-4. Write a program that prints the distinct words in its input
 * sorted into decreasing order of frequency of occurrence. Precede each word
 * by its count.
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
 *   goodbye, goodbyeworld
 *
 *   zebrafoot
 *
 *
 */

#define MAXWORDLEN 100
#define MAXLINESLEN 100

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct WordNode {
    char *word;
    struct WordNode *left;
    struct WordNode *right;
    int *linenos;
};

char *get_word();
void insert_word(char *word, struct WordNode *tree);
void print_words(struct WordNode *tree);
int count_occurances(struct WordNode *node);

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

/* Global values */
int lineno = 1;

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

void print_word(struct WordNode *node)
{
    printf("%d: ", count_occurances(node));

    int *linenos = NULL;
    printf("%s: ", node->word);
    linenos = (int *) node->linenos;


    while (*linenos != 0) {
        /* will always rely on there being an extra zero */
        if (*(linenos + 1) != 0)
            printf("%d, ", *linenos);
        else
            printf("%d", *linenos);
        linenos++;
    }
    putchar('\n');

}

/* Count the linenos to know how many times each word occurs */
/* Of course this could have been tracked in stuct, possible optimization */
int count_occurances(struct WordNode *node)
{
    int count = 0;
    int *linenos = (int *) node->linenos;

    while (*linenos != 0) {
        /* will always rely on there being an extra zero */
        linenos++;
        count++;
    }
    return count;
}

void print_words(struct WordNode *tree)
{
    if (tree->left != NULL)
        print_words(tree->left);
    if (tree->word != NULL) {
        print_word(tree);
    }
    if (tree->right != NULL)
        print_words(tree->right);
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
        if (c == '\n')
            lineno++;
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

void insert_word(char *word, struct WordNode *tree)
{
    int *linenos;
    /* initialize root if empty */
    if (tree->word == NULL) {
        tree->word = word;
        linenos = malloc(sizeof(int[MAXLINESLEN + 1])); /* extra byte for termination */
        linenos[0] = lineno;
        tree->linenos = linenos;
        return;
    }

    int lr = strcmp(word, tree->word);
    if (lr == 0) {
        /* already in tree */

        /* Add new line number so skip already used (sorry n^2)
         * leave extra zero for termination */
        int l;
        for (l = 0; tree->linenos[l] != 0 && l < MAXLINESLEN; l++) {
        }
        if (l == MAXLINESLEN)
            printf
                ("Number of line number on a %s exceeded max value of %d.\n",
                 tree->word, MAXLINESLEN);
        else
            tree->linenos[l] = lineno;
        return;
    }

    linenos = malloc(sizeof(int[MAXLINESLEN]));
    linenos[0] = lineno;

    struct WordNode **lrnode;
    if (lr < 0) {
        lrnode = &(tree->left);
    } else if (lr > 0) {
        lrnode = &(tree->right);
    }
    if (*lrnode == NULL) {
        *lrnode = malloc(sizeof(struct WordNode));

        **lrnode = (struct WordNode) { word, NULL, NULL, linenos };
    } else {
        insert_word(word, *lrnode);
    }
}

/* Zebra */
/* Apple */
/* zebra */
/* zebra */
/* zebra */
/* zebra */
/* zebra */
/* zebra */
/* zebra */
/* zebra */
