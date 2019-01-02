#ifndef MALLOC_H
# define MALLOC_H

#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

# define TINY 'T'
# define SMALL 'S'
# define LARGE 'L'

# define TINY_BLOCK 1024
# define SMALL_BLOCK 1024 * 32

#define TRUE 1
#define FALSE 0

#define SIZE_T_MAX 18446744073709551615UL

typedef unsigned int t_my_bool;

/*
** according pdf
*/
# define MIN_ALLOCATION_PER_ZONE 100

typedef struct	s_block {
	void			*zone;
	void			*next_address;
	size_t			data_size;
    t_my_bool	    is_free;
	void			*ptr_data;
}				t_block;

typedef struct	s_zone {
	t_block		*start_block;
	void		*next_zone;
	void		*previous_zone;
	size_t		size;
	char		type;
}				t_zone;

extern void			*g_start_address;

/*
** malloc.c
*/
void			*malloc(size_t size);
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
** zone_release.c
*/
t_my_bool       is_need_release_zone(t_zone *zone);
t_my_bool       zone_is_empty(t_zone *zone);
void            release_zone(t_zone *zone);


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
t_my_bool       is_block_exist(t_block *check_block);


/*
** realloc.c
*/
void            *realloc(void *ptr, size_t size);
t_block         *find_new_space(t_block *block, size_t size);
t_my_bool       block_fusion_realloc(t_block *block, size_t new_size);
t_block         *new_allocation(t_block *block, size_t new_size);
void            data_copy(void *dst, void *src, size_t len);


/*
** free.c
*/
void	        free(void *ptr);
void            release_block(t_block *block);
void            block_fusion_free(t_block *block);


/*
** show_alloc_mem.c
*/
void            show_alloc_mem(void);
void            show_zone_memory(void);
void            show_block_memory(t_block *block);
void	        ft_puthex(unsigned int number);
void            fill_zero_ascii(char *str, size_t len);


/*
** libft functions
*/
void	        ft_bzero(void *s, size_t n);
void	        *ft_memset(void *b, int c, size_t len);
void	        ft_putchar(char c);
void	        ft_putnbr(size_t n);
void	        ft_putstr(char const *s);


#endif


