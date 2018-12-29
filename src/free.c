#include "../include/malloc.h"

void	ft_free(void *ptr)
{
	t_block	*block;
	t_zone	*zone;

	if (!ptr || !g_start_address)
	{
		return ;
	}
	block = (t_block*)(ptr - sizeof(t_block));
	if (is_block_exist(block) == FALSE)
	{
		return ;
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

	next_block = (t_block*)block->next_address;
	block->is_free = TRUE;
	if (block->next_address && next_block->is_free == TRUE)
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

	next_block = (t_block*)block->next_address;
	block->data_size = block->data_size + sizeof(t_block) +
			next_block->data_size;
	block->next_address = next_block->next_address;
}

