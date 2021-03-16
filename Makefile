
NAME = test

SOURCEDIR = ./srcs/

INCLUDES = ./includes/

PARSER = $(SOURCEDIR)parser/
BMP = $(SOURCEDIR)bmp/
DISPLAY = $(SOURCEDIR)display/
EVENTS = $(SOURCEDIR)events/
MAIN = $(SOURCEDIR)main/
RAYCAST = $(SOURCEDIR)raycast/

SRCS = $(MAIN)main.c \
	$(MAIN)init.c \
	$(MAIN)exit_game.c \
	$(RAYCAST)cub.c \
	$(RAYCAST)sprite_cast.c \
	$(PARSER)info_parser.c \
	$(PARSER)map_parser.c \
	$(PARSER)parser_utils.c \
	$(PARSER)main_parser.c \
	$(PARSER)flood_fill.c \
	$(DISPLAY)visu2d.c \
	$(DISPLAY)bresenham.c\
	$(DISPLAY)display.c \
	$(DISPLAY)sprite_draw.c \
	$(EVENTS)events.c \
	$(BMP)save_bmp.c \
	





OBJS := ${SRCS:c=o}

CC = clang -g $(FLAGS)

FLAGS = -I. -I$(INCLUDES) -Wall -Werror -Wextra 
LIBS = ./libft
UNAME := $(shell uname)
APPLE = Darwin

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDES)
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
