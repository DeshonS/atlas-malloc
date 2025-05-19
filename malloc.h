struct meta_block {
	size_t size;
	struct meta_block *next;
	int free;
};

#define META_SIZE sizeof(struct meta_block)

#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stddef.h>

void *_malloc(size_t size);
struct meta_block *request_space(struct meta_block* last, size_t size);
struct meta_block *find_free_block(struct meta_block **last, size_t size);