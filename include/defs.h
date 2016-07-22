#ifndef DEFS_H_W6EWNPFH
#define DEFS_H_W6EWNPFH

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#include "err_code.h"

#define ERROR_MAP(XX)       \
  XX(INVALID_HDR, "message header is valid")      \
  XX(CHECK_FAILED, "crc32 check sum checks fail") \
  XX(MESSAGE_INCOMP, "uncompelete message")      \
  XX(MALLOC_FAILED, "memory allocate failed")     \
  XX(BUFFER_OVERFLOW, "the buffer overflow and drop packet")\
  XX(EMPTY_BUFFER, "empty buffer assigned")   \
  XX(NOT_ENOUGH_DATA, "not enough data for parse")

typedef enum{
  OK = 0,
#define XX(code, _) ERR_ ##code = _ERR_##code,
  ERROR_MAP(XX)
#undef XX
  ERROR_NUM
} errorno_t;

#endif /* end of include guard: DEFS_H_W6EWNPFH */
