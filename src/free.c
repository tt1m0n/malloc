#include "../include/malloc.h"

void	free(void *ptr)
{
	t_block	*block;

	if (!ptr || !g_start_address)
	{
		return;
	}
	block = (t_block*)(ptr - sizeof(t_block));
	if (is_block_exist(block) == FALSE)
	{
		return;
	}
	if (block->is_free == TRUE)
	{
		return;
	}
	release_block(block);
}

void    release_block(t_block *block)
{
	t_block *next_block;

	next_block = block->next_block;
	block->is_free = TRUE;
	if (block->next_block && next_block->is_free == TRUE)
	{
		block_fusion_free(block);
	}
	if (is_need_release_zone(block->zone) == TRUE)
	{
		release_zone(block->zone);
	}
}

void       block_fusion_free(t_block *block)
{
	t_block *next_block;

	next_block = block->next_block;
	block->data_size = block->data_size + sizeof(t_block) +
			next_block->data_size;
	block->next_block = next_block->next_block;
}

