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

struct meta_block
{
	size_t size;
	struct meta_block *next;
	int free;
	union
	{
		long l;
		void *p;
		double d;
		long double ld;
    } align;
};

void *_malloc(size_t size);
struct meta_block *request_space(struct meta_block* last, size_t size);
struct meta_block *find_free_block(struct meta_block **last, size_t size);

#endif
