#ifndef MESSAGE_H_MKWXB4AV
#define MESSAGE_H_MKWXB4AV

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus__
extern "C"{
#endif

#define HDR_BYTES   10
#define CRC_BYTES   4
typedef struct message_s message_t;

enum message_type{
  RESERVED = 0x01,
  TEXT     = (0x01) << 1,
  IMG      = (0x01) << 2,
  EMOJI    = (0x01) << 3,
  URL      = (0x01) << 4,
  QUIT     = (0x01) << 5,
  UNKNOWN  = (0x01) << 6
};

struct message_s {
  uint8_t     flags;
  uint8_t     type;
  uint32_t    to_uid;
  uint32_t    body_len;
  uint32_t    crc32;
  uint8_t     body[0];
};


typedef int (*msg_cb)(const message_t *msg);

int read_msg_from_buffer(uint8_t *buffer, size_t buffer_len, message_t *msg, msg_cb cb);

int write_msg_to_buffer(const message_t* msg, uint8_t* buffer, size_t* write_len, msg_cb cb);

static int read_headers(uint8_t* buffer, size_t buffer_len, message_t* msg);

uint32_t cal_crc32(uint8_t *buffer, size_t buffer_len);

#define FLAGS 0x17
#define VALID_FLAGS(flags) (!((flags)^FLAGS))

#ifdef __cplusplus__
}
#endif

#endif /* end of include guard: MESSAGE_H_MKWXB4AV */
