#ifndef _DEFS_H_
#define _DEFS_H_ 1

#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

#define CONTAINER_OF(ptr, type, member)         \
    ((type *)((char *)(ptr) - offsetof(type, member)))

#ifdef DEBUG
  #define LOGFMT(fmt, params...)      printf(fmt "\n", params)
  #define LOGERR(fmt, params...)      fprintf(fmt "\n", params)
  #define LOGMSG(msg)                 puts(msg)
#else
  #define LOGFMT(fmt, params...)
  #define LOGERR(fmt, params...)
  #define LOGMSG(msg)
#endif

#define BUILD_BUG_ON(condition)             \
  ((void)sizeof(char[1-2*!!(condition)]))

#define ASSERT(expr)                assert((expr))
#define ASSERT_NOT(expr)            assert(!(expr))
#define ASSERT_EQ(x,y)              assert((x) == (y))
#define ASSERT_LS(x, y)             assert((x) < (y))
#define ASSERT_GT(x,y)              assert((x) > (y))
#define ASSERT_LE(x,y)              assert((x) <= (y))
#define ASSERT_GE(x,y)              assert((x) >= (y))

#define FATAL_ERROR(msg)                        \
    do {                                        \
        fprintf(stderr,                         \
                "Fatal Error in %s on line %d : %s\n"   \
                __FILE__,                               \
                __LINE__,                               \
                msg);                                   \
        fflush(stderr);                                 \
        abort();                                        \
    } while(0)


#define MAX(a, b)   ((a) > (b) ? (a) : (b))
#define MIN(a, b)   ((a) < (b) ? (a) : (b))

#define SWAP16(x)   ((((x)&0xff00)>>8)|(((x)&0x00ff)<<8))
#define SWAP32(x)   ((((x)&0xff000000)>>24) |(((x)&0x00ff0000)>>8) | \
                    (((x)&0x0000ff00<<8) | (((x)&0x000000ff)<<24)))
#define SWAP64(x)   ((((x)&0xff00000000000000ULL)>>56) | (((x)&0x00ff000000000000ULL)>>40) | \
                    (((x)&0x0000ff0000000000ULL)>>24) | (((x)&0x000000ff00000000ULL)>>8) | \
                    (((x)&0x00000000ff000000ULL)<<8) | (((x)&0x0000000000ff0000ULL)<<24) |\
                    (((x)&0x000000000000ff00ULL)<<40) | (((x)&0x00000000000000ffULL)<<56))

#endif
