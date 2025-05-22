#ifndef MALLOC_H
#define MALLOC_H

#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
    #include <stdalign.h>
    #define ALIGNMENT alignof(max_align_t)
#else
    #define ALIGNMENT sizeof(void *)
#endif

#define ALIGN_UP(x, a)   (((x) + ((a) - 1)) & ~((a) - 1))
#define META_SIZE ALIGN_UP(sizeof(struct meta_block), ALIGNMENT)

/**
 * struct meta_block - A structure to represent a block of memory.
 * @size: The size of the block.
 * @next: A pointer to the next block.
 * @free: A flag indicating if the block is free or not.
 */

struct meta_block
{
	size_t size;
	struct meta_block *next;
	int free;

	alignas(max_align_t) char _align_pad;
};





void *_malloc(size_t size);
struct meta_block *request_space(struct meta_block *last, size_t size);
struct meta_block *find_free_block(struct meta_block **last, size_t size);

#endif
