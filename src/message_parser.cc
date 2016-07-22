#include "message_parser.h"
#include "defs.h"
#include "message.h"
#include "utils.h"

int init_parse_ctx(parse_ctx* ctx)
{
  ctx->cur_state = INIT;
  ctx->cur_offset = 0;
  ctx->buffer = 0;
  return OK;
}

int assign_buffer(parse_ctx* ctx, buffer_t *p_buff)
{
  if(0 == p_buff)
    return ERR_EMPTY_BUFFER;

  ctx->buffer = p_buff;
  return OK;
}

int parse(parse_ctx* ctx, message_t *msg, parsed_cb p_cb)
{

  size_t start = ctx->cur_offset;
  uint8_t *p = ctx->buffer->data + start;
  int r = 0;
  switch(ctx->cur_state) {
  case INIT: {
    if(ctx->cur_offset + 1 > ctx->buffer->len)
      return ERR_NOT_ENOUGH_DATA;
    msg->flags = *p++;
    ctx->cur_offset++;
    ctx->cur_state = FLAGS_PARSED;
  }
  case FLAGS_PARSED : {
    if(ctx->cur_offset + 1 > ctx->buffer->len)
      return ERR_NOT_ENOUGH_DATA;
    msg->type = *p++;
    ctx->cur_offset++;
    ctx->cur_state = TYPE_PARSED;
  }
  case TYPE_PARSED: {
    if(ctx->cur_offset + 4 > ctx->buffer->len)
      return ERR_NOT_ENOUGH_DATA;
    msg->to_uid = *p;
    msg->to_uid = SWAP32(msg->to_uid);
    p += 4;
    ctx->cur_offset += 4;
    ctx->cur_state = TO_UID_PARSED;
  }
  case TO_UID_PARSED : {
    if(ctx->cur_offset + 4 > ctx->buffer->len)
      return ERR_NOT_ENOUGH_DATA;
    msg->body_len = *p;
    msg->body_len = SWAP32(msg->body_len);
    p += 4;
    ctx->cur_offset += 4;
    ctx->cur_state = BODY_LEN_PARSED;
  }
  case BODY_LEN_PARSED : {
    if(ctx->cur_offset + msg->body_len > ctx->buffer->len)
      return ERR_NOT_ENOUGH_DATA;
    int nread = peek_bytes(ctx->buffer, ctx->cur_offset, msg->body_len, msg->body);
    ASSERT((size_t)nread == msg->body_len);
    p += msg->body_len;
    ctx->cur_state = BODY_PARSED;
    ctx->cur_offset += msg->body_len;
  }
  case BODY_PARSED : {
    if(ctx->cur_offset + 4 > ctx->buffer->len)
      return ERR_NOT_ENOUGH_DATA;
    msg->crc32 = *p;
    msg->crc32 = SWAP32(msg->crc32);
    p += 4;
    ctx->cur_offset += 4;
    ctx->cur_state = CRC_PARSED;
  }
  case CRC_PARSED : {
    if(!VALID_FLAGS(msg->flags))
      return ERR_INVALID_HDR;
    uint32_t crc32 = cal_crc32(ctx->buffer->data + start, sizeof(*msg) + msg->body_len - CRC_BYTES);
    if(!(crc32 ^ msg->crc32))
      return ERR_CHECK_FAILED;
  }
  case FINISH: {
    erase_by_range(ctx->buffer, start, ctx->cur_offset);
    ctx->cur_offset = start;
    ctx->cur_state = INIT;
    if(p_cb)
      r = p_cb(msg);
    break;
  }
  default:
    break;
  }
  return r;
}

int destroy_parse_ctx(parse_ctx* ctx)
{
  if(ctx->buffer)
    destroy_block(ctx->buffer);
  
  if(ctx)
    free(ctx);

  return OK;
}
