ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
NAME_LINK = libft_malloc.so

PATH_SRC = ./src/

PATH_INC = ./include

INCLUDES = -I $(PATH_INC)

FLAGS = -Wall -Wextra -Werror $(INCLUDES) -fPIC

#_____________FILES____________#

SRC = malloc.c free.c realloc.c block_creation.c block_operations.c\
        ft_bzero.c ft_memset.c ft_putchar.c ft_putnbr.c ft_putstr.c\
        helpers.c show_alloc_mem.c zone_creation.c zone_operations.c zone_release.c\
		calloc.c reallocf.c show_mem_bonuses.c


OBJ = $(addprefix $(PATH_SRC), $(SRC:.c=.o))

#____________RULES_____________#

all: $(NAME)

$(NAME): $(OBJ)
	$(DEL_LINK)
	gcc $(FLAGS) $(OBJ) -o $(NAME) -shared
	ln -s $(NAME) $(NAME_LINK)

$(OBJ): %.o: %.c
	gcc -c $(FLAGS) $< -o $@

DEL_LINK = rm -rf $(NAME_LINK)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	$(DEL_LINK)

re: fclean all

.PHONY: clean all fclean re
