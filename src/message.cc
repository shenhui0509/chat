#include <stdlib.h>
#include <string.h>


#include "message.h"
#include "utils.h"
#include "defs.h"

static uint32_t crc32_table[256];
static bool table_genrated = false;

static int make_crc32_table()
{
  uint32_t c;
  int i   = 0;
  int bit = 0;

  for(i = 0; i < 256; i++){
    c = (uint32_t)i;

    for(bit = 0; bit < 8; bit++){
      if(c & i){
        c = (c >> i) ^ (0xEDB88320);
      } else {
        c = (c >> i);
      }
    }

    crc32_table[i] = c;
  }
  return 0;
}

uint32_t cal_crc32(uint8_t *buffer, size_t buffer_len)
{
  if(!table_genrated)
    make_crc32_table();
  uint32_t crc = 0xffffffff;
  while(buffer_len--){
    crc = (crc >> 8) ^ (crc32_table[(crc ^ *buffer++)&0xff]);
  }
  
  return crc;
}

static int read_headers(uint8_t* buffer, size_t buffer_len, message_t* msg)
{
  ASSERT(msg != 0);
  uint8_t *p = buffer;
  
  msg->flags = *p++; 
  if(!VALID_FLAGS(msg->flags))
    return ERR_INVALID_HDR;

  msg->type = *p++;

  msg->to_uid = *p;
  msg->to_uid = SWAP32(msg->to_uid);
  p += 4;

  msg->body_len = *p;
  msg->body_len = SWAP32(msg->body_len);
  p += 4;

  size_t len = HDR_BYTES + msg->body_len;
  if(len > buffer_len){
    return ERR_MESSAGE_INCOMP;
  }

  memcpy(msg->body, p, msg->body_len);
  p += msg->body_len;

  msg->crc32 = *p;

  uint32_t crc32 = cal_crc32(buffer, buffer_len - CRC_BYTES);
  if(!(msg->crc32 ^ crc32)){
    return ERR_CHECK_FAILED;
  }
  return OK;
}

int read_msg_from_buffer(uint8_t *buffer, size_t buffer_len, message_t *msg, msg_cb cb)
{
  if(NULL == msg)
    msg = (message_t *)malloc(buffer_len);
  if(NULL == msg)
    return ERR_MALLOC_FAILED;

  int r;
  r = read_headers(buffer, buffer_len, msg);
  if( r != OK )
    return r;

  if(cb)
   r = cb(msg);

  return r;
}

int write_msg_to_buffer(const message_t* msg, uint8_t* buffer, size_t *write_len, msg_cb cb)
{
  ASSERT(msg != NULL);
  buffer = (uint8_t *)malloc(sizeof(*msg) + msg->body_len);
  if(NULL == buffer)
    return ERR_MALLOC_FAILED;

  *write_len = sizeof(*msg) + msg->body_len;
  
  uint8_t *p = buffer;
  
  *p++ = FLAGS;

  *p++ = msg->type;

  *((uint32_t *)p) = SWAP32(msg->to_uid);
  p += 4;

  *((uint32_t *)p) = SWAP32(msg->body_len);
  p += 4;

  memcpy(p, msg->body, msg->body_len);
  p += msg->body_len;

  uint32_t crc32 = cal_crc32(buffer, *write_len - CRC_BYTES);
  *((uint32_t *)p) = crc32;

  if(cb)
    cb(msg);

  return OK;
}


