NAME = libftprintf.a
FLAGS = -Wall -Werror -Wextra -g
CC = gcc
OBJ = $(patsubst %, %.o, $(SRC))

SRC += dispatcher
SRC += storeflags
SRC += conversion_diou
SRC += conversion_sc
SRC += conversion_xp
SRC += printflags
SRC += misc
SRC += ulitobase
SRC += ft_bzero
SRC += ft_isalpha
SRC += ft_isdigit
SRC += ft_memset
SRC += ft_strlen

all: $(NAME)

$(NAME): $(OBJ)
	@ echo "Compiling ft_printf library..."
	@ ar -rcs $(NAME) $(OBJ)

%.o: %.c
	@ echo "Compiling $<..."
	@ $(CC) $(FLAGS) -c $< -o $@ -g

clean:
	@ /bin/rm -f $(OBJ)
	@ echo "Cleaning folders..."

fclean: clean
	@ /bin/rm -f $(NAME)

re: fclean all
	@ echo "Library Remade"
