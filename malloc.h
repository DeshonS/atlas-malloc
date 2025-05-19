#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stddef.h>
#include <stdalign.h>

struct meta_block {
	size_t size;
	struct meta_block *next;
	int free;
	alignas(max_align_t) char _align_pad;
};

#define META_SIZE sizeof(struct meta_block)

void *_malloc(size_t size);
struct meta_block *request_space(struct meta_block* last, size_t size);
struct meta_block *find_free_block(struct meta_block **last, size_t size);