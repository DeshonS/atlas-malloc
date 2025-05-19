#include "malloc.h"

struct meta_block *find_free_block(struct meta_block **last, size_t size) {
	struct meta_block *current = global_base;
	while (current && !(current->free && current->size >= size)) {
		*last = current;
		current = current->next;
	}
	return current;
}

struct meta_block *request_space(struct meta_block* last, size_t size)
{
	struct meta_block *block;
	block = sbrk(0);
	void *request = sbrk(size + META_SIZE);
	assert((void*)block == request);
	if (request == (void*) -1)
	{
		return NULL;
	}

	if (last)
	{
		nast->next = block;
	}
	block->size = size;
	block->next = NULL;
	block->free = 0;
	return block;
}

void *malloc(size_t size)
{
	struct meta_block *block;
	if (size <= 0)
	{
		return NULL;
	}
	if (!global_base)
	{
		block = request_space(NULL, size);
		if (!block)
		{
			return NULL;
		}
		global_base = block;
	}
	else
	{
		struct meta_block *last = global_base;
		block = find_free_block(&last, size);
		if (!block)
		{
			return NULL;
		}
		else
		{
			struct meta_block *last = global_base;
			block = find_free_block(&last, size);
			if (!block)
			{
				block = request_space(last, size);
				if (!block)
				{
					return NULL;
				}
			}
			else
			{
				block->free = 0;
			}
		}
	}
	return (block + 1);
}
