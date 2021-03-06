/* Exercise 8-2. Rewrite fopen and _fillbuf with fields instead of explicit bit
 * operations. 
 *
 * So we have the file opening and reading correctly, but I have to use GDB to confirm that because I don't have _flushbuf...yet
 * */


#include <stdlib.h>
/* #include <stdio.h> */

/* system headers */
#include <sys/types.h>          /* for open */
#include <sys/stat.h>           /* for open */
#include <fcntl.h>              /* for open */
#include <unistd.h>             /* for close */

#define STDIN_FD 0
#define STDOUT_FD 1

#define PERMS 0666              /* RW for owner, group, others */

/* #define NULL      0 */
#define EOF       (-1)
#define BUFSIZ    1024
#define OPEN_MAX  20            /* max #files open at once */

typedef struct _iobuf {
    int cnt;                    /* characters left */
    char *ptr;                  /* next character position */
    char *base;                 /* location of buffer */
    struct _flags {
        unsigned int _READ:1;   /* file open for reading */
        unsigned int _WRITE:1;  /* file open for writing */
        unsigned int _UNBUF:1;  /* file is unbuffered */
        unsigned int _EOF:1;    /* EOF has occurred on this file */
        unsigned int _ERR:1;    /* error occurred on this file */
    } flag;                     /* mode of file access */
    int fd;                     /* file descriptor */
} FILE;
extern FILE _iob[OPEN_MAX];

#define stdin   (&_iob[0])
#define stdout  (&_iob[1])
#define stderr  (&_iob[2])

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define    feof(p)     (((p)->flag &_EOF) != 0)
#define    ferror(p)   (((p)->flag &_ERR) != 0)
#define    fileno(p)   ((p)->fd)

#define getc(p)   (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))

/* we dont have flush buffer yet */
/* #define putc(x,p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x),p)) */
/* #define putc(x,p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : (*(p)->ptr++ = (x))) */

#define getchar()   getc(stdin)
#define putchar(x)  putc((x), stdout)

FILE _iob[OPEN_MAX] = {         /* stdin, stdout, stderr: */
    { 0, (char *) 0, (char *) 0, {._READ = 1}, 0 },
    { 0, (char *) 0, (char *) 0, {._WRITE = 1}, 1 },
    { 0, (char *) 0, (char *) 0, {._WRITE = 1,._UNBUF = 1}, 2 }
};

FILE *myfopen(char *name, char *mode);


int main(int argc, char *argv[])
{
    FILE *fp;
    char mymode = 'r';
    if (argc == 2)
        fp = myfopen(argv[1], &mymode);
    else {
        exit(3);
    }

    char c;
    c = getc(fp);
    c = getc(fp);
    c = getc(fp);
    c = getc(fp);
    exit((int) c);
}


/* fopen:  open file, return file ptr */
FILE *myfopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if ((fp->flag._READ == 0) && (fp->flag._WRITE == 0))
            break;              /* found free slot */
    if (fp >= _iob + OPEN_MAX)  /* no free slots */
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {

        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else
        fd = open(name, O_RDONLY, 0);
    if (fd == -1)               /* couldn't access name */
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    if (*mode == 'r')
        fp->flag._READ = 1;
    else
        fp->flag._WRITE = 1;
    return fp;
}

/* _fillbuf:  allocate and fill input buffer */
int _fillbuf(FILE * fp)
{
    int bufsize;

    if ((fp->flag._READ == 1)
        && ((fp->flag._EOF == 1) || (fp->flag._ERR == 1)))
        return EOF;

    bufsize = (fp->flag._UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL)       /* no buffer yet */
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;         /* can't get buffer */
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {

        if (fp->cnt == -1)
            fp->flag._EOF = 1;
        else
            fp->flag._ERR = 1;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

#define BOTTOM 1
