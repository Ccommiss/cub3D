
NAME = test


SRCS = cub.c \
	parser.c \
	visu2d.c \
	./getnextline/get_next_line.c \
	./getnextline/get_next_line_utils.c \


OBJS := ${SRCS:c=o}

CC = clang -g $(FLAGS)

FLAGS =  -Wall -Werror -Wextra -O3 -fsanitize=null -fsanitize=address -fsanitize=object-size -fsanitize=nonnull-attribute -fsanitize=pointer-overflow -fsanitize-address-use-after-scope
LIBS = ./libft/

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -L$(LIBS) -lft  -o $(NAME)

clean:
	rm *.o

fclean: clean
	rm $(NAME)

re : fclean all
