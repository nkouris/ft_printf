NAME = libft.a
FLAGS = -Wall -Wextra -Werror -c -I
CC = gcc
OBJ = $(SRC:.c=.o) 

SRC += ft_bzero.c
SRC += ft_isalpha.c
SRC += ft_isdigit.c
SRC += ft_memset.c
SRC += ft_strlen.c

all: $(NAME)

$(NAME): $(SRC)
	@ echo "Building libft..."
	@ $(CC) $(FLAGS) libft.h $(SRC)
	@ ar -rcs $(NAME) $(OBJ)

clean:
	@ echo "Cleaning folder..."	
	@ /bin/rm -f $(OBJ)

fclean: clean
	@ /bin/rm -f $(NAME)

re: fclean all
