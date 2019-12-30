/* Exercise 8-1. Rewrite the program cat from Chapter 7 using read, write, open
 * and close instead of their standard library equivalents. Perform experiments
 * to determine the relative speeds of the two versions. 
 *
 * Test and benchmark:
 *
 * $ make
 * echo Know its working
 * Know its working
 * ./mycat_old test.txt
 * Hello
 * This is a file
 * ./mycat test.txt
 * Hello
 * This is a file
 * echo Benchmark
 * Benchmark
 * time ./mycat_old bench.txt >/dev/null
 *
 * real    0m0.115s
 * user    0m0.115s
 * sys     0m0.000s
 * time ./mycat bench.txt >/dev/null
 *
 * real    0m0.006s
 * user    0m0.001s
 * sys     0m0.005s
 * [y2k@15r 8-1]
 * $ ./mycat_old
 * sdf
 * sdf
 * sdf
 * sdf
 * ggggg
 * ggggg
 * [y2k@15r 8-1]
 * $ ./mycat
 * sdf
 * sdf
 * dddddd
 * dddddd
 * adsf
 * adsf
 */


#include <stdlib.h>
#include <stdio.h>

/* system headers */
#include <sys/types.h>          /* for open */
#include <sys/stat.h>           /* for open */
#include <fcntl.h>              /* for open */
#include <unistd.h>             /* for close */

#define STDIN_FD 0
#define STDOUT_FD 1

void filecopy(int ifd, int ofd);

/* cat:  concatenate files, version 2 */
int main(int argc, char *argv[])
{
    int fd;
    char *prog = argv[0];       /* program name for errors */

    if (argc == 1)              /* no args; copy standard input */
        filecopy(STDIN_FD, STDOUT_FD);
    else
        while (--argc > 0)
            if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                exit(1);
            } else {
                filecopy(fd, STDOUT_FD);
                close(fd);
            }
    exit(0);
}

/* filecopy:  copy file ifp to file ofp */
void filecopy(int ifd, int ofd)
{
    int n;
    char buf[BUFSIZ];

    while ((n = read(ifd, buf, BUFSIZ)) > 0)
        if (write(ofd, buf, n) != n) {
            fprintf(stderr, "filecopy: write error on file descriptor %d",
                    ofd);
        }
}
