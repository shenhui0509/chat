#ifndef BLOCK_T_H_RUKCOL4I
#define BLOCK_T_H_RUKCOL4I

#include <stdint.h>
#include <stdlib.h>
#ifdef __cplusplus__
extern "C"{
#endif

typedef struct block_s block_t;

struct block_s{
  size_t len;
  uint8_t data[0];
};

block_t* allocate_block(size_t len);

int destroy_block(block_t* p);

block_t* duplicate_block(block_t* p);

#ifdef __cplusplus__
}
#endif

#endif /* end of include guard: BLOCK_T_H_RUKCOL4I */
