/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 15:47:33 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/26 15:47:34 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	int			size;
	char		buf[BUFFER_SIZE];
	static char *stock = NULL;
	int			i;

	i = 0;
	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0 || read(fd, buf, 0) < 0)
		return (-1);
	while ((((size = read(fd, buf, BUFFER_SIZE)) > 0)) || (stock && stock[i]))
	{
		if (size > 0)
			stock = ft_strconcat(stock, buf, size);
		while (stock[i] && stock[i] != '\n')
			i++;
		if (stock[i] == '\n')
		{
			*line = ft_fill_line(stock, i, *line);
			stock = ft_newstock(&stock, i + 1);
			return (1);
		}
	}
	*line = ft_fill_line(stock, i, *line);
	free(stock);
	stock = NULL;
	return (0);
}
