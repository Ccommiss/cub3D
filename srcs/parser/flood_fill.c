/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:18:45 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/26 15:08:38 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**  load_sprite
**
** 	[synopsis] : set the dirx & diry positions according to letter found in game
** 	[call] : in check_borders (part of flood fill algorithm)
** 	[return] : none
*/

int		load_sprite(t_data *data, int x, int y)
{
	static int	i;

	if (!data->spr)
	{
		i = 0;
		data->spr = (t_spr *)malloc(sizeof(t_spr));
		if (!data->spr)
			return (-1);
		data->spr->head = data->spr;
	}
	else
	{
		data->spr->next = (t_spr *)malloc((sizeof(t_spr)));
		if (!data->spr->next)
			return (-1);
		data->spr->next->head = data->spr->head;
		data->spr = data->spr->next;
	}
	data->spr->index = i++;
	data->spr->x = x;
	data->spr->y = y;
	data->spr->distance = 0;
	data->spr->next = NULL;
	return (1);
}

void	check_borders(t_data *data, int x, int y, char ***mapbis)
{
	if (y < 0 || y >= data->map_h || x < 0 || x >= data->map_w
		|| data->map[y][x] == ' ' || data->map[y][x] == '	')
	{
		data->error = MAP_NOT_CLOSED;
		return ;
	}
	if (data->map[y][x] == '1' || mapbis[0][y][x] == 'v')
		return ;
	if (ft_is_in_str("0SNEW", data->map[y][x]))
		mapbis[0][y][x] = 'v';
	if (data->map[y][x] == '2' && data->error == 0)
	{
		mapbis[0][y][x] = 'v';
		if (load_sprite(data, x, y) == -1)
			data->error = MALLOC_ERROR;
	}
	if (data->error == 0)
	{
		check_borders(data, x + 1, y, mapbis);
		check_borders(data, x - 1, y, mapbis);
		check_borders(data, x, y + 1, mapbis);
		check_borders(data, x, y - 1, mapbis);
	}
	return ;
}

int		free_copymap(int nb_alloc, char ***copymap, int ret)
{
	int	i;

	i = 0;
	while (i < nb_alloc)
		free(copymap[0][i++]);
	free(*copymap);
	return (ret);
}

int		flood_fill(t_data *data)
{
	char	**copymap;
	int		i;

	i = 0;
	copymap = (char **)malloc((sizeof(char *)) * (data->map_h + 1));
	if (!copymap)
		return (close_win(data));
	while (i < data->map_h)
	{
		copymap[i] = (char *)malloc(10 * data->map_w);
		if (!copymap[i])
			return (free_copymap(i, &copymap, -1));
		ft_memset(copymap[i], '.', data->map_w);
		i++;
	}
	copymap[i] = NULL;
	check_borders(data, data->pos_x, data->pos_y, &copymap);
	free_copymap(data->map_h, &copymap, 1);
	if (data->error != 0)
		return (error_message(data, data->error));
	return (1);
}
