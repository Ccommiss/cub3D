# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/16 15:08:11 by ccommiss          #+#    #+#              #
#    Updated: 2021/03/17 18:06:29 by ccommiss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_isalnum.c \
	ft_isprint.c \
	ft_memcmp.c \
	ft_putchar_fd.c \
	ft_split.c \
	ft_strlcat.c \
	ft_strncmp.c \
	ft_substr.c \
	ft_atoi.c \
	ft_isalpha.c \
	ft_itoa.c \
	ft_memcpy.c \
	ft_putendl_fd.c \
	ft_strchr.c  \
	ft_strlcpy.c \
	ft_strnstr.c \
	ft_tolower.c\
	ft_bzero.c \
	ft_isascii.c \
	ft_memccpy.c \
	ft_memmove.c \
	ft_putnbr_fd.c \
	ft_strdup.c \
	ft_strlen.c \
	ft_strrchr.c \
	ft_toupper.c \
	ft_calloc.c \
	ft_isdigit.c \
	ft_memchr.c \
	ft_memset.c  \
	ft_putstr_fd.c \
	ft_strjoin.c \
	ft_strmapi.c \
	ft_strtrim.c

CUSTOM = ft_putstr.c \
	ft_putnbr.c \
	ft_putchar.c \
	ft_swap_strings.c \
	ft_swap_char.c \
	ft_reverse.c \
	ft_strncat.c \
	ft_memdel.c \
	ft_strncpy.c \
	ft_strequ.c \
	ft_itoa_base.c \
	ft_strtoupper.c \
	ft_utoa.c \
	ft_ftoa.c \
	ft_isempty.c \
	ft_free_double_tab.c

BONUS = ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c \
	get_next_line.c \
	get_next_line_utils.c \
	ft_is_in_str.c

FLAGS = -Wall -Werror -Wextra
OBJS = $(SRCS:.c=.o) $(CUSTOM:.c=.o) $(BONUS:.c=.o)
OBJS_BONUS = $(BONUS:.c=.o)
NORME = norminette
CC = @clang -c -g $(FLAGS)


# This is a minimal set of ANSI/VT100 color codes
_END=$'\x1b[0m
_BOLD=$'\x1b[1m
_UNDER=$'\x1b[4m
_REV=$'\x1b[7m
_LIGHT=$'\x1b[2m

# Colors
_GREY=$'\x1b[30m
_RED=$'\x1b[31m
_GREEN=$'\x1b[32m
_YELLOW=$'\x1b[33m
_BLUE=$'\x1b[34m
_PURPLE=$'\x1b[35m
_CYAN=$'\x1b[36m
_WHITE=$'\x1b[37m
_LBLUE=$'\x1b[94m
_ORANGE=$'\x1b[38;5;215m
_PINK=$'\x1b[38;5;95m
_GRASS=$'\x1b[38;5;119m
_UNICORN= $'\360\237\246\204
_UNIC=$'🦄
_LETTER = $'💌

WP = `pwd | sed 's!.*/!!'`


all : message $(NAME)
	@printf "$(_BOLD)$(_PINK)%-30s$(_END) $(_GRASS)$(_BOLD)%s$(_END)\n" [$(WP)] "✅	Your $(NAME) is ready."

message :
	@printf "$(_BOLD)$(_PINK)%-30s$(_END) $(_WHITE)$(_LIGHT)%s$(_END)\n" [$(WP)] "Your $(NAME) files are compiling..."

$(NAME): $(SRCS) $(OBJS)
	@ar -rc $(NAME) $(OBJS)
	@ranlib $(NAME)

bonus : all $(BONUS) $(OBJS_BONUS)
	@ar -rc $(NAME) $(OBJS_BONUS)
	@ranlib $(NAME)
	@printf "$(_BOLD)$(_PINK)%-30s$(_END) %s\n" [$(NAME)] "Your $(NAME) is ready, bonuses included."

norme:
	@$(NORME) $(SRCS) $(BONUS)

normebonus: norme
	@$(NORME) $(BONUS)

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)
	@printf "$(_BOLD)$(_PINK)%-30s$(_END) $(_LIGHT)%s\n$(_END)" [$(WP)] "Your .o files have been deleted."

fclean: clean
	@rm -f $(NAME)
	@printf "$(_BOLD)$(_PINK)%-30s$(_END) $(_BOLD)%s\n$(_END)" [$(WP)] "🗑️	Your $(NAME) have been deleted. "

re: fclean all

.PHONY: all clean re norme bonus normebonus
