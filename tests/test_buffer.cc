#include <string.h>
#include <stdlib.h>

#include "buffer.h"
#include "block_t.h"
#include "gtest/gtest.h"

static const char str1[] = "0123456789";
static const char str2[] = "0123456789abcdef";

TEST(TEST_NEW_BUFFER, buffer)
{
  buffer_t* p_buff = new_buffer();
  ASSERT_EQ(p_buff->len, 0);
  free(p_buff);
}

TEST(TEST_PUSH, buffer)
{
  buffer_t* p_buff = new_buffer();
  block_t* p_blk = allocate_block(10);
  memcpy(p_blk->data, str1, 10);
  push_block(p_buff, p_blk);
  ASSERT_EQ(p_buff->len, 10);
  p_blk = allocate_block(16);
  memcpy(p_blk->data, str2, 16);
  push_block(p_buff, p_blk);
  ASSERT_EQ(p_buff->len, 26);
  free(p_buff);
}

TEST(TEST_PEAK, buffer)
{
  buffer_t* p_buff = new_buffer();
  block_t* p_blk = allocate_block(10);
  memcpy(p_blk->data, str1, 10);
  push_block(p_buff, p_blk);
  p_blk = allocate_block(16);
  memcpy(p_blk->data, str2, 16);
  push_block(p_buff, p_blk);

  uint8_t buf[32];
  memset(buf, '\0', 32);
  peek_bytes(p_buff, 0, 10, buf);
  ASSERT_STREQ((char *)buf, str1);
  peek_bytes(p_buff, 2, 11, buf);
  ASSERT_STREQ((char *)buf, "23456789012");
  peek_bytes(p_buff, 10, 17, buf);
  ASSERT_EQ(p_buff->len, 26);
  ASSERT_EQ(strlen((char *)buf), 16);
  ASSERT_STREQ((char *)buf, str2);
  peek_bytes(p_buff, 20, 17, buf);
  buf[6] = '\0';
  ASSERT_STREQ((char *)buf, "abcdef");
  free(p_buff);
}

TEST(TEST_REAS, buffer)
{
  buffer_t* p_buff = new_buffer();
  block_t* p_blk = allocate_block(10);
  memcpy(p_blk->data, str1, 10);
  push_block(p_buff, p_blk);
  p_blk = allocate_block(16);
  memcpy(p_blk->data, str2, 16);
  push_block(p_buff, p_blk);
  
  uint8_t pbuf[32];
  memset(pbuf, '\0', 32);

  read_bytes(p_buff, 10, pbuf);
  ASSERT_STREQ((char *)pbuf, "0123456789");
  free(p_buff);
}

int main(int argc, char* argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


