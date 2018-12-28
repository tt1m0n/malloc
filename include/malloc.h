#ifndef MALLOC_H
# define MALLOC_H

#include <sys/mman.h>
#include <unistd.h>

# define TINY 'T'
# define SMALL 'S'
# define LARGE 'L'

# define TINY_BLOCK 1024
# define SMALL_BLOCK 1024 * 32

#define TRUE 1
#define FALSE 0

typedef unsigned int t_my_bool;

/*
** according pdf
*/
# define MIN_ALLOCATION_PER_ZONE 100

typedef struct	s_block {
	void			*zone;
	// check how it uses
	void			*previous_address;
	void			*next_address;
	size_t			data_size;
	unsigned int	is_free;
	void			*ptr_data;
}				t_block;

typedef struct	s_zone {
	t_block		*start_block;
	void		*current_zone;
	void		*next_zone;
	void		*previous_zone;
	size_t		size;
	char		type;
}				t_zone;

extern void			*g_start_address;

/*
** malloc.c
*/
void			*ft_malloc(size_t size);
t_block			*get_block(t_zone *start_zone, size_t size);


/*
** helpers.c
*/
char 			get_block_type(size_t data_size);


/*
** zone_creation.c
*/
t_zone			*start_zone_init(size_t data_size);
t_zone			*get_new_zone(size_t data_size, char block_type);
size_t			get_size_to_allocate(size_t block_size);
void			*zone_allocate(size_t size_to_allocate);
t_zone			*add_new_zone(t_zone *zone, size_t data_size);


/*
** zone_operations.c
*/
void			zone_init(size_t size_of_allocation,
					char block_type, t_zone *ptr_zone);
t_zone			*get_correct_type_zone(t_zone *start_zone,
					size_t data_size);
t_my_bool 		is_correct_type_zone(t_zone* zone,
					size_t data_size);
t_my_bool		is_available_space_zone(t_zone *zone,
					size_t data_size);

/*
** block_creation.c
*/
t_block			*add_block_to_zone(t_zone *zone, size_t size_data);


/*
** block_operations.c
*/
void			block_init(t_zone *zone, t_block *ptr_block,
					size_t data_size);
t_block			*get_available_block(t_block *block, size_t data_size);
t_block			*get_free_block(t_block *block);
void 			set_block_to_used(t_block *block, size_t data_size);


#endif


