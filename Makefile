
NAME = test


TST = test_minilibx.c

OBJ := ${TST:c=o}

SRCS = cub.c \
	parser.c \
	visu2d.c \
	bresenham.c\
	./getnextline/get_next_line.c \
	./getnextline/get_next_line_utils.c \


OBJS := ${SRCS:c=o}

CC = clang -g $(FLAGS)

FLAGS =  -Wall -Werror -Wextra -O3 -fsanitize=address
LIBS = ./libft/

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -L$(LIBS) -lft  -o $(NAME)

clean:
	rm *.o

fclean: clean
	rm $(NAME)

re : fclean all
