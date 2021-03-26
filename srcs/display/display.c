/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:08:46 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/26 15:03:51 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	my_mlx_pixel_put
**
** 	[synopsis] : draws a pixel
**  [call] : everytime needing a pixel
**	[return] : none
*/

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->imgaddr + (y * data->line_length + x
			* (data->bits_per_pixel / 8));
	if (x >= 0 && x < data->width && y >= 0 && y < data->height)
		*(unsigned int *)dst = color;
}

/*
**	define_move
**
** 	[synopsis] : defines if player is moving
**			> used for minimap displaying :
**			if you do not move, you are able to
**			iterate through the whole map
**  [call] : display
**	[return] : none
*/

void	define_move(t_data *data)
{
	static double	pos[2];

	if (data->v.move == 2)
	{
		data->v.move = 1;
		return ;
	}
	if (pos[0] == 0 && pos[1] == 0)
	{
		pos[0] = data->pos_x;
		pos[1] = data->pos_y;
	}
	if (pos[0] != data->pos_x || pos[1] != data->pos_y)
		data->v.move = 1;
	else
		data->v.move = 0;
	pos[0] = data->pos_x;
	pos[1] = data->pos_y;
}

int		display(t_data *data)
{
	fill_black(data);
	fill_ceiling(data);
	fill_floor(data);
	wall_casting(data);
	if (data->displaymap == 1)
	{
		define_move(data);
		set_compass(data);
		set_player(data);
		set_map(data);
		set_player(data);
		data->color = 0xffffff;
	}
	else if (data->displaymap == 0)
		set_mapicon(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	if (data->displaymap == 1)
		display_pos(data);
	return (1);
}
