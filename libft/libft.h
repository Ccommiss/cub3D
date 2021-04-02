/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:06:14 by ccommiss          #+#    #+#             */
/*   Updated: 2021/04/02 13:07:29 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include "get_next_line.h"

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

/*
**   <CHAR> :  functions related to characters
*/
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isalpha(int c);
int				ft_isprint(int c);
int				ft_isalnum(int c);
int				ft_tolower(int c);
int				ft_toupper(int c);

/*
**   <NBR> :  functions related to numbers
*/
int				ft_atoi(const char *nptr);
char			*ft_itoa(int n);
char			*ft_itoa_base(long unsigned n, int base);
char			*ft_utoa(unsigned int n);
char			*ft_ftoa(float n, int afterpoint);
void			ft_putnbr(int nbr);
void			ft_putnbr_fd(int n, int fd);

/*
**   <STR> :  functions  related  to  strings
*/
void			ft_putstr(char *str);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
int				ft_strncmp(const char *f, const char *s, size_t len);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strdup(const char *s);
char			*ft_strtoupper(char *str);

/*
**  <STR> :  functions  related  to strings not  belonging  to  libc
*/
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/*
**  <FT_MEM>  : functions  related  to memory
*/

void			ft_bzero(void *s, size_t n);
void			*ft_memset(void *s, int c, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t size);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memmove(void *s1, const void *s2, size_t n);
int				ft_memcmp(const void *ptr1, const void *ptr2, size_t size);
void			*ft_calloc(size_t elementcount, size_t elementsize);

/*
**   <FT_LST>  : functions related to strings
*/

t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *lst);
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstadd_front(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *l, void *(*f)(void *), void (*del)(void *));

/*
**   <PERSO>   :  my custom functions
*/

int				ft_mystrncmp(const char *f, const char *s, size_t len);
void			ft_memdel(void **ptr);
char			*ft_strncat(char *dest, const char *src, size_t n);
char			*ft_strncpy(char *dest, const char *src, size_t n);
void			ft_swap_strings(char **one, char **two);
void			ft_swap_char(char *one, char *two);
char			*ft_reverse(char *str);
void			ft_putendl(char const *s);
int				ft_strequ(char const *s1, char const *s2);
int				ft_isempty(char *str);
void			ft_free_double_tab(char **tab);
int				ft_is_in_str(const char *s, int c);

#endif
