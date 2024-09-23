#ifndef BLOCK_META_
#define BLOCK_META_
#include <sys/types.h>
#include <unistd.h>

// A meta block is always referred to by a pointer
typedef struct block_meta *t_block;

struct block_meta {
  size_t size;
  t_block next;
  t_block prev;
  int free;
};

#define META_SIZE sizeof(struct block_meta)

t_block find_free_block(void *global_base, t_block *last_ptr, size_t size);
t_block request_space(void *global_base, t_block last, size_t size);

t_block get_t_block(void *addr);

#endif
