
NAME = test


SRCS = cub.c parser.c ./getnextline/get_next_line.c ./getnextline/get_next_line_utils.c

OBJS := ${SRCS:c=o}

CC = clang -g

FLAGS =  -Wall -Werror -Wextra -fsanitize=address

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm *.o

fclean: clean
	rm *.a

re : fclean all
