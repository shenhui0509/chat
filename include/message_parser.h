#ifndef MESSAGE_PARSER_H_GNTU8Q3T
#define MESSAGE_PARSER_H_GNTU8Q3T

#include <stdlib.h>
#include <stddef.h>

#include "buffer.h"
#include "message.h"
#ifdef __cplusplus__
extern "C"{
#endif

#define PARSE_CTX_INIT {0}

enum parse_state_t{
  INIT = 0,
  FLAGS_PARSED,
  TYPE_PARSED,
  TO_UID_PARSED,
  BODY_LEN_PARSED,
  BODY_PARSED,
  CRC_PARSED,
  FINISH
};

typedef struct parse_ctx parse_ctx;

struct parse_ctx {
  parse_state_t   cur_state;
  size_t          cur_offset;
  buffer_t*       buffer;
};

typedef int (*parsed_cb)(message_t *);

int init_parse_ctx(parse_ctx* ctx);

int assign_buffer(parse_ctx* ctx, buffer_t* buffer);

int parse(parse_ctx* ctx, message_t* msg, parsed_cb p_cb);

int destroy_parse_ctx(parse_ctx* ctx);

#ifdef __cplusplus__
}
#endif

#endif /* end of include guard: MESSAGE_PARSER_H_GNTU8Q3T */
