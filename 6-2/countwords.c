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
 *
 *  What do they mean by "groups?"
 *
 *  hello_:
 *     hello
 *
 *  goodby:
 *      goodbye
 *      goodbyeworld
 *
 *  zebraf:
 *      zebrafoot
 * */

#include <stdlib.h>

int main()
{
    exit(0);
}
