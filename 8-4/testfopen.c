/* Exercise 8-4. The standard library function
 *
 *     int fseek(FILE *fp, long offset, int origin)
 *
 * is identical to lseek except
 * that fp is a file pointer instead of a file descriptor and the return value
 * is an int status, not a position. Write fseek. Make sure that your fseek
 * coordinates properly with the buffering done for the other functions of the
 * library. */

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
#define BUFSIZ    16
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

int _fillbuf(FILE * stream);
int _flushbuf(int, FILE * stream);
int fflush(FILE * stream);
int fclose(FILE * stream);
int fseek(FILE * fp, long offset, int origin);

#define    feof(p)     (((p)->flag &_EOF) != 0)
#define    ferror(p)   (((p)->flag &_ERR) != 0)
#define    fileno(p)   ((p)->fd)
/* if the count is zero read new chars to buffer */
#define getc(p)   (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
/* if the count is zero flush the buffer and write a new char to buffer */
#define putc(x,p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x),p))
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
    if (argc != 2)              /* pass a filename */
        exit(3);

    fp = myfopen(argv[1], "r");

    char c;
    while ((c = getc(fp)) != EOF)
        putc(c, stdout);
    fflush(NULL);

    fseek(fp, 7, SEEK_SET);
    while ((c = getc(fp)) != EOF)
        putc(c, stdout);
    fclose(fp);
    fflush(stdout);
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

    /* must be open for read */
    if (fp->flag._READ == 0)
        return EOF;

    if ((fp->flag._EOF == 1) || (fp->flag._ERR == 1))
        return EOF;

    int bufsize;
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

/* _flushbuf:  allocate and flush input buffer */
int _flushbuf(int c, FILE * fp)
{
    /* must be open for write */
    if (fp->flag._WRITE == 0)
        return EOF;

    if ((fp->flag._EOF == 1) || (fp->flag._ERR == 1))
        return EOF;

    int bufsize;
    bufsize = (fp->flag._UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL) {     /* no buffer yet */
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;         /* can't get buffer */
    } else {
        /* if we already had a buffer, write it */
        if (write(fp->fd, fp->base, fp->ptr - fp->base) < 0)
            fp->flag._ERR = 1;
    }
    fp->ptr = fp->base;
    fp->cnt = bufsize;

    if (c != EOF) {
        *(fp->ptr++) = (char) c;
        fp->cnt--;
    }
    return (unsigned char) *fp->ptr;
}

/* fflush: flush FILE or if NULL, all open FILE buffers */
int fflush(FILE * stream)
{
    /* flush all if no stream provided */
    if (stream == NULL) {
        for (int fpn = 0; fpn < OPEN_MAX; fpn++) {
            /* If the stream argument is NULL, fflush() flushes
             * all open output streams. */
            if (_iob[fpn].flag._WRITE)
                fflush(&_iob[fpn]);
        }
        return 0;
    }

    if (stream->flag._READ)
        return _fillbuf(stream);
    else if (stream->flag._WRITE)
        return _flushbuf(EOF, stream);
    else
        return EOF;
}

/* fclose: function flushes the stream pointed to by stream
* (writing any buffered output data using fflush and closes the
* underlying file descriptor. */
int fclose(FILE * stream)
{
    if (stream == NULL)
        return EOF;

    fflush(stream);
    close(stream->fd);
    free(stream->base);
    stream->cnt = 0;
    stream->ptr = NULL;
    stream->base = NULL;
    stream->flag._ERR = 0;
    stream->flag._EOF = 0;
    stream->flag._READ = 0;
    stream->flag._WRITE = 0;
    stream->flag._UNBUF = 0;
    stream->fd = 0;

    return 0;
}

/* fseek: like lseek */
int fseek(FILE * fp, long offset, int origin)
{
    if (!fp->flag._READ)
        return EOF;

    if (lseek(fp->fd, offset, origin) < 0)
        return EOF;

    _fillbuf(fp);
    return 0;
}

#define BOTTOM 1
