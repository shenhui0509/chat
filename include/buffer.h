#ifndef BUFFER_H_O4NUDCC7
#define BUFFER_H_O4NUDCC7

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#include "block_t.h"
#ifdef __cplusplus__
extern "C" {
#endif

/* the max buffer size */
static const size_t max_buffer_size = 1 << 20;

typedef struct block_s buffer_t;

buffer_t* new_buffer();

/* Push a block into the buffer */
/* Block will be dropped if the buffer overflows */
/* return 0 on success; ERR_OVERFLOW < 0 on buffer overflows */
int push_block(buffer_t* p_buff, block_t* p_blk);

/* Erase by range [start, end) */
/* return n_erased :
 * if n_erased >= 0: n_erased bytes are successfully erased from buffer
 */
int erase_by_range(buffer_t* p_buff, size_t start, size_t end);

/* Erased by len
 * return n_erased
 */
int erase_by_len(buffer_t* p_buff, size_t offset, size_t len);


int peek_bytes(buffer_t* p_buff, size_t offset, size_t len,
              uint8_t* dst);

/* read the first len bytes into dst
 * then erase it from the buffer
 * return n_readed
 */
int read_bytes(buffer_t* p_buff, size_t len, uint8_t* dst);


#ifdef __cplusplus__
}
#endif
#endif /* end of include guard: BUFFER_H_O4NUDCC7 */
