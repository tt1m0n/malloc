#include "../include/malloc.h"

void        *realloc(void *ptr, size_t size)
{
    t_block *current_block;
    t_block *new_block;
    t_zone  *current_zone;

    if (!ptr || !g_start_address)
        return (malloc(size));
    current_block = (t_block*)(ptr - sizeof(t_block));
    if (is_block_exist(current_block) == FALSE)
        return (NULL);
    if (current_block->is_free == TRUE)
        return (NULL);
    current_zone = (t_zone*)current_block->zone;
    if (is_correct_type_zone(current_zone, size) == TRUE)
        new_block = find_new_space(current_block, size);
    else
        new_block = new_allocation(current_block, size);
    if (!new_block)
        return (NULL);
    return (new_block->ptr_data);
}

t_block     *find_new_space(t_block *block, size_t size)
{
    if (block->data_size >= size)
    {
        block->data_size = size;
        return block;
    }
    else if (block_fusion_realloc(block, size) == TRUE)
    {
        block->data_size = size;
        /*
        ** set next address
        */
        if (block->next_address)
        {
            block->next_address =
                    ((t_block*)block->next_address)->next_address;
        }
        return (block);
    }
    else
    {
        return new_allocation(block, size);
    }
}

t_my_bool   block_fusion_realloc(t_block *block, size_t new_size)
{
    t_block *next_block;

    if (!block)
    {
        return (FALSE);
    }
    next_block = (t_block*)block->next_address;
    if (!next_block  || !next_block->is_free)
    {
        return (FALSE);
    }
    if (block->data_size + sizeof(t_block) + next_block->data_size >= new_size)
    {
        return (TRUE);
    }
    return (FALSE);
}

t_block     *new_allocation(t_block *block, size_t new_size)
{
    t_block *new_block;
    void    *ptr;

    ptr = malloc(new_size);
    if (!ptr)
    {
        return (NULL);
    }
    new_block = (t_block*)(ptr - sizeof(t_block));
    if (new_block)
    {
        data_copy(new_block->ptr_data, block->ptr_data, block->data_size);
        free(block->ptr_data);
    }
    return (new_block);
}

void        data_copy(void *dst, void *src, size_t len)
{
    size_t i;

    i = 0;
    while(i < len)
    {
        ((char*)dst)[i] = ((char*)src)[i];
        i++;
    }
}



























