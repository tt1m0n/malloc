ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
NAME_LINK = libft_malloc.so

PATH_SRC = ./src/

PATH_INC = ./include

CC = gcc

ifeq ($(DEBUG),yes)
	CFLAGS = $(INCLUDES) -g -fPIC
	LDFLAGS = -shared
else
	CFLAGS = -Wall -Wextra -Werror $(INCLUDES) -fPIC
	LDFLAGS = -shared
endif

#_____________FILES____________#

SRC = malloc.c \


OBJ = $(addprefix $(PATH_SRC), $(SRC:.c=.o))

#____________RULES_____________#

.PHONY: clean fclean re test

all: $(NAME)

$(NAME): $(OBJ)
	# make -C libft/
	# $(CC) $(OBJ) -o $(NAME) $(LIBS) $(LDFLAGS)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
	ln -s $(NAME) $(NAME_LINK)

#____CLEAN____#

clean:
	rm -f $(OBJ)

#___FCLEAN___#

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_LINK)

#____RE____#

re: fclean all
