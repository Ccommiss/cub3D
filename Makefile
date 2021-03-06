
NAME = test

SOURCEDIR = ./srcs/

SRCS = $(SOURCEDIR)cub.c \
	$(SOURCEDIR)parser.c \
	$(SOURCEDIR)visu2d.c \
	$(SOURCEDIR)bresenham.c\
	$(SOURCEDIR)init.c \
	$(SOURCEDIR)parser_utils.c \
	$(SOURCEDIR)display.c \
	$(SOURCEDIR)events.c \
	$(SOURCEDIR)save_bmp.c \
	$(SOURCEDIR)sprite_cast.c \
	$(SOURCEDIR)sprite_draw.c 


OBJS := ${SRCS:c=o}

CC = gcc $(FLAGS)

FLAGS =  -Wall -Werror -Wextra 
LIBS = ./libft

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBS)
	$(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -L$(LIBS) -lft  -o $(NAME)

clean:
	rm $(OBJS)
	make clean -C ./libft

fclean: clean
	rm $(NAME)

re : fclean all
