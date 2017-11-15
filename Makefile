NAME = libftprintf.a
FLAGS = -Wall -Werror -Wextra
CC = gcc
OBJ = $(patsubst %, %.o, $(SRC))

SRC += dispatcher
SRC += storeflags
SRC += conversion_one
SRC += printflags
SRC += misc
SRC += ft_bzero
SRC += ft_isalpha
SRC += ft_isdigit
SRC += ft_memset
SRC += ft_strlen

all: $(NAME)

$(NAME): $(OBJ)
	@ echo "Compiling with ft_printf..."
	@ ar -rcs $(NAME) $(OBJ)

%.o: %.c
	@ echo "Compiling $<..."
	@ $(CC) $(FLAGS) -c $< -o $@ -g

clean:
	@ /bin/rm -f $(OBJ)
	@ echo "Cleaning folders..."

fclean: clean

re: fclean all
	@ echo "Remake..."
