#ifndef __ext_h__
#define __ext_h__

/*==================== Imports ====================*/

#include <stdlib.h>


/*=================== Functions ===================*/

#define sizeof_cs(count, size)          ( ((size_t) (count)) * ((size_t) (size)) )

#define sizeof_ct(count, type)          sizeof_cs(count, sizeof(type))


#define malloc_cs(count, size)          malloc(sizeof_cs(count, size))

#define malloc_s(size)                  malloc(size)

#define malloc_ct(count, type)          malloc(sizeof_ct(count, type))

#define malloc_t(type)                  malloc(sizeof(type))


#define calloc_cs(count, size)          calloc(count, size)

#define calloc_s(size)                  calloc(1, size)

#define calloc_ct(count, type)          calloc(count, sizeof(type))

#define calloc_t(type)                  calloc(1, sizeof(type))


#define char_to_num(c)                  ( (c) - '0' )

#define num_to_char(n)                  ( (n) + '0' )


/*=================================================*/

#endif
