
NAME = test

TST = test_minilibx.c

OBJ := ${TST:c=o}

SRCS = cub.c \
	parser.c \
	visu2d.c \
	bresenham.c\
	init.c \
	parser_utils.c \
	display.c \
	events.c \
	save_bmp.c \
	sprite_cast.c \
	sprite_draw.c \
	./getnextline/get_next_line.c \
	./getnextline/get_next_line_utils.c \


OBJS := ${SRCS:c=o}

CC = gcc $(FLAGS)

FLAGS =  -Wall -Werror -Wextra 
LIBS = ./libft/

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -L$(LIBS) -lft  -o $(NAME)

clean:
	rm *.o

fclean: clean
	rm $(NAME)

re : fclean all
