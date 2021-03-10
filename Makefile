
NAME = test

SOURCEDIR = ./srcs/

SRCS = $(SOURCEDIR)cub.c \
	$(SOURCEDIR)info_parser.c \
	$(SOURCEDIR)map_parser.c \
	$(SOURCEDIR)visu2d.c \
	$(SOURCEDIR)bresenham.c\
	$(SOURCEDIR)init.c \
	$(SOURCEDIR)parser_utils.c \
	$(SOURCEDIR)display.c \
	$(SOURCEDIR)events.c \
	$(SOURCEDIR)save_bmp.c \
	$(SOURCEDIR)sprite_cast.c \
	$(SOURCEDIR)sprite_draw.c \
	$(SOURCEDIR)exit_game.c



OBJS := ${SRCS:c=o}

CC = clang -g $(FLAGS)

FLAGS =  -Wall -Werror -Wextra -fsanitize=address
LIBS = ./libft
UNAME := $(shell uname)
APPLE = Darwin

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBS)
ifeq ($(UNAME),$(APPLE))
	$(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -L$(LIBS) -lft  -o $(NAME)
endif
ifeq ($(UNAME),Linux)
	$(CC) $(OBJS) -L$(LIBS) -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
endif

clean:
	rm $(OBJS)
	make clean -C ./libft

fclean: clean
	rm $(NAME)

re : fclean all
