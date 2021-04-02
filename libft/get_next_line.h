/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 13:07:22 by ccommiss          #+#    #+#             */
/*   Updated: 2021/04/02 13:07:23 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 42
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

int		get_next_line(int fd, char **line);
char	*ft_fill_line(char *stock, int i, char *line);
char	*ft_strconcat(char *s1, char *s2, int size);
char	*ft_newstock(char **stock, int i);

#endif
