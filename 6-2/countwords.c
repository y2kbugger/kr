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
 * What do they mean by "groups?"
 *
 *   hello
 *
 *   goodbye
 *   goodbyeworld
 *
 *   zebrafoot
 * */

#include <stdlib.h>

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

    exit(0);
}

print_words(*words)
{
    ;
}

get_word()
{
    ;
}
