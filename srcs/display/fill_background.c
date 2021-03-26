/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:59:05 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/26 14:59:07 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	fill_black
**
** 	[synopsis] : fills the image with black and
**				avoids re-creating an image each time.
**  [call] : display
**	[return] : none
*/

void	fill_black(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->height - 1)
	{
		while (j < data->width - 1)
		{
			my_mlx_pixel_put(data, j, i, 0x000000);
			j++;
		}
		j = 0;
		i++;
	}
}

/*
**	fill_ceiling
**
** 	[synopsis] : fills ceiling.
**  [call] : display
**	[return] : none
*/

void	fill_ceiling(t_data *data)
{
	int	i;
	int	j;
	int	limit;

	i = 0;
	j = 0;
	limit = data->height * (int)(1 - (int)data->look) + data->jump;
	if (limit <= 0)
		limit = data->height;
	while (i < limit)
	{
		while (j < data->width)
		{
			my_mlx_pixel_put(data, j, i, data->info->ceiling_rgb);
			j++;
		}
		j = 0;
		i++;
	}
}

/*
**	fill_floor
**
** 	[synopsis] : fills floor.
**  [call] : display
**	[return] : none
*/

void	fill_floor(t_data *data)
{
	int	i;
	int	j;

	i = data->height * data->look + data->jump;
	j = 0;
	while (i < data->height)
	{
		while (j < data->width)
		{
			my_mlx_pixel_put(data, j, i, data->info->floor_rgb);
			j++;
		}
		j = 0;
		i++;
	}
}
