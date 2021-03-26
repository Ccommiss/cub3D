/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:17:09 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/26 11:19:32 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**  ft_finddir
**
** 	[synopsis] : set the dirx & diry positions according to letter found in game
** 	[return] : none
*/

void	ft_finddir(t_data *data, char dir)
{
	data->dirx = 0.0;
	data->diry = 0.0;
	if (dir == 'N')
		data->diry = -1;
	else if (dir == 'S')
		data->diry = 1;
	else if (dir == 'E')
		data->dirx = 1;
	else if (dir == 'W')
		data->dirx = -1;
}

/*
**  ft_realloc_tab
**
** 	[synopsis] : realloc all data->map[y] lines, in case a line is
**				longer than the previous ones
** 	[return] : 1 if success, -1 if malloc fails
*/

int	ft_realloc_tab(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < y)
	{
		data->map[i] = (char *)ft_realloc(data->map[i],
				data->map_w, sizeof(char) * x + 1);
		if (!data->map[i])
			return (close_win(data));
		data->map[i][data->map_w] = '\0';
		i++;
	}
	data->map_w = x;
	return (1);
}

/*
**  fill_maptab
**
** 	[synopsis] : fill the data->map tab (char **map) with the line
** 	[return] : 1 if success, -1 if fails
*/

int	fill_maptab(t_data *data, char *line, int y)
{
	int	x;
	int	i;
	int j;

	x = 0;
	i = 0;
	j = 0;
	while (line[j] && data->error == 0)
	{
		if (ft_check_chars(line[j], data, x, y) == -1)
			return (-1);
		else if (ft_check_chars(line[j], data, x, y) == 1)
			data->map[y][x] = line[j++];
		else if (ft_check_chars(line[j++], data, x, y) == 2)
			data->map[y][x] = '0';
		x++;
	}
	data->map[y][x] = '\0';
	if (x > data->map_w)
		ft_realloc_tab(data, x, y);
	return (1);
}

/*
**  ft_parse_map
**
** 	[synopsis] : allocate memory
** 			> Verifies if the line is blank at the beginning – simply returns 0
** 			> Reallocates the double tab at each call (one more Y each time a
**				line is read)
** 			> Allocates the map[y] with :
**				1/ line length if it's > the saved width,
**				2/ the saved width if it's <=
** 	[call] : ft_parse (in main_parser.c)
** 	[return] : - 1 if a malloc fails (and sets Malloc Error in
**			main parser before properly exiting), or 1 if success
*/

int	ft_parse_map(t_data *data, char *line)
{
	static int	y;
	int			len;

	if ((y == 0) && ft_isempty(line))
		return (0);
	if (data->map_h == 0)
		y = 0;
	data->map_h = y + 1;
	data->map = (char **)ft_realloc(data->map, (data->map_h) * sizeof(char *),
			(data->map_h + 1) * sizeof(char *));
	if (!data->map)
		return (-1);
	data->map[data->map_h] = 0;
	if (data->map_w == 0 || ft_strlen(line) > (size_t)data->map_w)
		len = ft_strlen(line) + 1;
	else
		len = data->map_w + 1;
	data->map[y] = (char *)malloc(sizeof(char) * (len));
	if (!data->map[y])
		return (-1);
	ft_bzero(data->map[y], len);
	fill_maptab(data, line, y);
	data->map[++y] = 0;
	return (1);
}
