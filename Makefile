NAME = libftprintf.a
FLAGS = -Wall -Werror -Wextra -c -I
CC = gcc
LIBFT = inc/libft.a 
OBJ = $(SRC: .c=.o)

SRC += dispatcher.c
SRC += storeflags.c
SRC += conversion_one.c
SRC += conversion_two.c
SRC += processflags.c
SRC += ulitoabase.c

all: $(NAME)

$(NAME): $(LIBFT) $(SRC)
	@ echo "Compiling with ft_printf..."
	@ $(CC) $(FLAGS) $(LIBFT)
	@ ar -rcs $(NAME) $(OBJ)

$(LIBFT):
	@ make -C inc

clean:
	@ echo "Cleaning folders..."
	@ /bin/rm -f $(OBJ)
	@ make -C inc clean

fclean: clean
	@ echo "Removing lib file..."
	@ make -C inc fclean

re: fclean all
	@ echo "Remake..."
