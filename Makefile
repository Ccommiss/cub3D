
NAME = test


SRCS = cub.c

OBJS := ${SRCS:c=o}

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm *.o

fclean: clean
	rm *.a

re : fclean all
