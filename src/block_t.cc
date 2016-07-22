#include <string.h>
#include "block_t.h"

block_t* allocate_block(size_t len)
{
  block_t* p_blk = (block_t *)malloc(sizeof(block_t) + len);
  p_blk->len = len;
  return p_blk;
}

int destroy_block(block_t* p_blk)
{
  if(0 != p_blk){
    free(p_blk);
    p_blk = 0;
  }
  return 0;
}

block_t* duplicate_block(block_t* p_blk)
{
  block_t* p_dup_blk = (block_t *)malloc(sizeof(block_t) + p_blk->len);
  memcpy(p_dup_blk, p_blk, sizeof(block_t) + p_blk->len);
  return p_dup_blk;
}
