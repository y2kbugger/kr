/* Exercise 8-6. The standard library function calloc(n,size) returns a pointer
 * to n objects of size size, with the storage initialized to zero. Write
 * calloc, by calling malloc or by modifying it. */


#define NULL (void*)0

typedef long Align;             /* for alignment to long boundary */

union header {                  /* block header: */
    struct {
        union header *ptr;      /* next block if on free list */
        unsigned size;          /* size of this block */
    } s;
    Align x;                    /* force alignment of blocks */
};

typedef union header Header;

static Header base;             /* empty list to get started */
static Header *freep = NULL;    /* start of free list */
static Header *morecore(unsigned);

void *y2kmalloc(unsigned nbytes);
void y2kfree(void *ap);

const int MALLOCSIZE = 500000;

int main()
{
    y2kmalloc(4000);
    return 0;
}


/* y2kmalloc:  general-purpose storage allocator */
void *y2kmalloc(unsigned nbytes)
{
    if (nbytes == 0) {
        return NULL;
    }
    if (nbytes > MALLOCSIZE) {
        return NULL;
    }
    Header *p, *prevp;
    unsigned nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    if ((prevp = freep) == NULL) {      /* no free list yet */
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {      /* big enough */
            if (p->s.size == nunits)    /* exactly */
                prevp->s.ptr = p->s.ptr;
            else {              /* allocate tail end */
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *) (p + 1);
        }
        if (p == freep)         /* wrapped around free list */
            if ((p = morecore(nunits)) == NULL)
                return NULL;    /* none left */
    }
}

#include <limits.h>
/* y2kcalloc:  general-purpose storage allocator */
void *y2kcalloc(unsigned int n, unsigned int nbytes)
{
    if ((n == 0) || (nbytes == 0))
        return NULL;
    unsigned int mallocbytes;
    if (__builtin_umul_overflow(n, nbytes, &mallocbytes))
        return NULL;
    else
        return y2kmalloc(n * nbytes);
}

#define    NALLOC    1024       /* minimum #units to request */

/* morecore:  ask system for more memory */
static Header *morecore(unsigned nu)
{
    char *cp, *sbrk(int);
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *) -1)      /* no space at all */
        return NULL;
    up = (Header *) cp;
    up->s.size = nu;
    y2kfree((void *) (up + 1));
    return freep;
}


/* y2kfree:  put block ap in free list */
void y2kfree(void *ap)
{
    Header *bp, *p;

    bp = (Header *) ap - 1;     /* point to block header */
    if (bp == NULL) {
        return;
    }
    if (bp->s.size == 0) {
        return;
    }
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;              /* freed block at start or end of arena */

    if (bp + bp->s.size == p->s.ptr) {  /* join to upper nbr */
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;
    if (p + p->s.size == bp) {  /* join to lower nbr */
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;
    freep = p;
}
