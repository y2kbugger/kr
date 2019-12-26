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
 * Example of how it could be stored as tree:
 *
 *        goodbye
 *       /      \
 *   hello     goodbyeworld
 *                   \
 *                   zebrafoot
 */

#include <stdlib.h>


struct WordNode {
    char *word;
    struct WordNode *left;
    struct WordNode *right;
};

void print_words(struct WordNode *rootnode);

/* Data for testing the printing program */

struct WordNode testtree = {
    "goodbye",
    NULL,
    NULL
};

/* struct WordNode { "hello", */
    /*                  0, */
    /*                  0 }; */
    /* , struct WordNode { */
    /*     "goodbyeworld", 0, struct WordNode { */
    /*     "zebrafoot", 0, 0}; */
    /* }; */

/* Command Line Settings */
int TEST = 1;

/* on by default for now, until we add arg handling */

int main()
{
    /* parse args */
    /* -t : print test words */
    /* -n : number of characters to consider a group */

    /* read in words from stdin */
    /* get pointer one word at a time, stored in dynamically allocated memory */
    /* should only return words that are "variable names" (how to detect by context?) */
    /* search tree for word, if not existing, store the word */
    /* otherwise free the memory */


    /* print out the "variable names" in groups */
    if (TEST)
        print_words(&testtree);
    exit(0);
}

void print_words(struct WordNode *rootnode)
{
    ;
}

char *get_word()
{
    char *word;
    word = "placeholder";
    return word;
}
