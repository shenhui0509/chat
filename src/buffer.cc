#include <string.h>

#include "utils.h"
#include "defs.h"
#include "buffer.h"

buffer_t* new_buffer()
{
  buffer_t* ret = allocate_block(max_buffer_size);
  ret->len = 0;
  if(0 == ret)
    return 0;
  return ret;
}

int push_block(buffer_t* p_buff, block_t* p_blk)
{
  if(0 == p_blk)
    return 0;

  if(p_blk->len + p_buff->len > max_buffer_size){
    LOGERR("current buffer size is %lu, max : %lu", p_buff->len, max_buffer_size);
    LOGERR("new block size is %lu, results in buffer overflow", p_blk->len);
    return ERR_BUFFER_OVERFLOW;
  }

  memcpy(p_buff->data + p_buff->len, p_blk->data, p_blk->len);
  p_buff->len += p_blk->len;
  destroy_block(p_blk);
  return OK;
}

int erase_by_range(buffer_t* p_buff, size_t start, size_t end)
{
  if(start >= p_buff->len){
    return 0;
  }

  if(end > p_buff->len){
    end = p_buff->len;
  }

  size_t len = end - start;
  uint8_t *src = p_buff->data + end;
  uint8_t *dst = p_buff->data + start;
  memmove(dst, src, len);
  p_buff->len -= len;
  return len;
}

int erase_by_len(buffer_t* p_buff, size_t offset, size_t len)
{
  if(offset >= p_buff->len)
    return 0;

  if(offset + len > p_buff->len)
    len = p_buff->len - offset;

  uint8_t *src = p_buff->data + offset + len;
  uint8_t *dst = p_buff->data + offset;
  memmove(dst, src, len);
  p_buff->len -= len;
  return len;
}

int peek_bytes(buffer_t* p_buff, size_t offset, size_t len, uint8_t* dst)
{
  if(offset >= p_buff->len)
    return 0;

  if(offset + len > p_buff->len)
    len = p_buff->len - offset;

  uint8_t *src = p_buff->data + offset;
  
  if(0 == dst){
    do{
      dst = (uint8_t *)malloc(len);  
    } while(0 != dst);
  }

  memcpy(dst, src, len);
  return len;
}

int read_bytes(buffer_t* p_buff, size_t len, uint8_t* dst)
{
  if(len > p_buff->len)
    len = p_buff->len;

  if(0 == dst){
    do{
      dst = (uint8_t *) malloc(len);
    } while(0 != dst);
  }

  memcpy(dst, p_buff->data, len);
  return len;
}
