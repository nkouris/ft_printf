NAME = libftprintf.a
FLAGS = -Wall -Werror -Wextra 
CC = gcc
OBJSRC = $(patsubst %, %.o, $(SRC))
OBJINC = $(patsubst %, %.o, $(INC))

SRC += src/dispatcher
SRC += src/storeflags
SRC += src/conversion_diou
SRC += src/conversion_sc
SRC += src/conversion_xp
SRC += src/printflags
SRC += src/misc
SRC += src/ulitobase
INC += inc/ft_bzero
INC += inc/ft_isalpha
INC += inc/ft_isdigit
INC += inc/ft_memset
INC += inc/ft_strlen
INC += inc/ft_memalloc
INC += inc/ft_memdel
INC += inc/ft_strcpy

all: $(NAME)

$(NAME): $(OBJINC) $(OBJSRC)
	@ echo "Building ft_printf library..."
	@ ar -rcs $(NAME) $(OBJSRC) $(OBJINC) 

%.o: %.c
	@ echo "Compiling $<..."
	@ $(CC) $(FLAGS) -c $< -o $@

clean:
	@ /bin/rm -f $(OBJSRC)
	@ /bin/rm -f $(OBJINC)
	@ echo "Cleaning folders of object files..."

fclean: clean
	@ /bin/rm -f $(NAME)
	@ echo "Removing library file..."

re: fclean all
	@ echo "Library Remade"
