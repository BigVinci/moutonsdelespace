
/**
 * @file mem.h
 * @author François Cayre <francois.cayre@grenoble-inp.fr>
 * @date Fri Nov  1 00:56:03 2013
 * @brief Memory.
 *
 * Memory.
 */

#ifndef _MEM_H_
#define _MEM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <strings.h>
#include <string.h>

#include "common/types.h"
#include "common/bits.h"
#include "common/notify.h"



typedef union {
    uint32_t _32;
    uint64_t _64;
} vsize;

typedef struct {
    char      *name;    /* nom du segment */
    byte      *content; /* (tableau de byte) the real address at which the bytes of the section is located */
    vaddr      start;   /* adresse de départ du segment */ 
    vsize      size;    /* taille du segment */ 
    uint32_t   attr;    /* an integer value corresponding to the access and execution permissions of the segment */
} segment;

typedef struct {
    vsize       extent; /* ??????? */
    uint32_t    nseg;   /* nombre de segment */ 
    segment    *seg;    /* tableau de segment */
} *mem;



#define R__   1
#define RW_   2
#define R_X   3
#define UNDEF 7 /* For optionnal sections (.rodata) */

#define PGSZ          4  /* Page size:  4K */
#define STACKSZ       8  /* Stack size: 8M */
#define STACKSZ_BYTES (STACKSZ*1024*1024)
#define NPAGES(b) ( (b) ? ( (b)>>10 ) ? ((b)>>10)/PGSZ : 1 : 0 )


#define RODATA      0
#define TEXT        1
#define DATA        2
#define BSS         3
#define HEAP        4 /* inutile pour ce projet */
#define LIBC_TEXT   5 /* contenu dans [lib] */
#define LIBC_DATA   6 /* contenu dans [lib] */
#define STACK       7 /* corespond à la pile */
#define VSYSCALL    8 /* CAUTION: Make sure this one is the very last */

#define LAST_SEG    ((VSYSCALL)+1)

#define SCN_ATTR(width, rights)  (((width==0x1?32:64)<<8)+rights)
#define SCN_RIGHTS(attr)         (((attr)&0x000000ff))
#define SCN_WIDTH(attr)          (((attr))>>8)

mem init_mem( uint32_t nseg );
int attach_scn_to_mem( mem vm, char *name, uint32_t attr );
int fill_mem_scn( mem vm, char *name, vsize sz, vaddr start, byte *content );
void print_mem( mem vm );
void del_mem( mem vm );

#ifdef __cplusplus
}
#endif

#endif /* _MEM_H_ */
