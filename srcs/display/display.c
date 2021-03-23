/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:08:46 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/23 20:33:16 by ccommiss         ###   ########.fr       */
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
	char *dst;

	dst = data->imgaddr + (y * data->line_length + x
	* (data->bits_per_pixel / 8));
	if (x >= 0 && x < data->width && y >= 0 && y < data->height)
		*(unsigned int *)dst = color;
}

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
	int i;
	int j;

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
	int i;
	int j;
	int limit;

	i = 0;
	j = 0;
	limit = data->height * (int)(1 - (int)data->look);
	if (limit <= 0)
		limit = data->height;
	while (i < limit)
	{
		//printf ("SKY = %f \n", data->height * (1 - data->look));
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
	int i;
	int j;

	i = data->height * data->look;
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

/*
**	fill_floor
**
** 	[synopsis] : fills floor.
**  [call] : display
**	[return] : none
*/


void define_move(t_data *data)
{
 	static double pos[2];

	if (data->v.move == 2)
	{
		data->v.move = 1;
		return;
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

int	display(t_data *data)
{
	t_bresenham b;

	fill_black(data);
	fill_ceiling(data);
	fill_floor(data);
	dda(data);

	b.pt1[X] = (data->pos_x + data->v.init_w) * data->minimap_size + data->v.center_w;
	b.pt1[Y] = (data->pos_y + data->v.init_h + 1) * data->minimap_size + data->v.center_h;
	b.pt2[X] = (data->pos_x + data->v.init_w + data->dirx) *  data->minimap_size + data->v.center_w;
	b.pt2[Y] = (data->pos_y + data->v.init_h + 1 + data->diry) * data->minimap_size + data->v.center_h;
	if (data->displaymap == 1)
	{
		define_move(data);
		set_compass(data);
		set_player(data);
		set_map(data);
		set_player(data);
		data->color = 0xffffff;
		bresenham(&b, data);
	}
	else if (data->displaymap == 0)
		set_mapicon(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	if (data->displaymap == 1)
		display_pos(data);
	return(1);
}
