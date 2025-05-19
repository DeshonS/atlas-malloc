#include "malloc.h"

void *global_base = NULL;

struct meta_block *find_free_block(struct meta_block **last, size_t size)
{
	struct meta_block *current = global_base;

	while (current && !(current->free && current->size >= size))
	{
		*last = current;
		current = current->next;
	}
	return (current);
}

struct meta_block *request_space(struct meta_block *last, size_t size)
{
	void *raw = sbrk(META_SIZE + ALIGNMENT + size);

	if (raw == (void *)-1)
	{
		return (NULL);
	}

	uintptr_t base = (uintptr_t)raw + META_SIZE;
	uintptr_t aligned = ALIGN_UP(base, ALIGNMENT);
	struct meta_block *block = (struct meta_block *)(aligned - META_SIZE);

	if (last)
	{
		last->next = block;
	}
	block->size = size;
	block->next = NULL;
	block->free = 0;
	return (block);
}

void *_malloc(size_t size)
{
	struct meta_block *block;

	if (size <= 0)
	{
		return (NULL);
	}
	if (!global_base)
	{
		block = request_space(NULL, size);
		if (!block)
		{
			return (NULL);
		}
		global_base = block;
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
				return (NULL);
			}
		}
		else
		{
			block->free = 0;
		}
	}
	return ((void *)((char *)block + META_SIZE));
}
