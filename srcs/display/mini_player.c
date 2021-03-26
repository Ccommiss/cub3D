/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 15:04:42 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/26 15:05:27 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		move_map(t_data *data, int direction, int wid_hei)
{
	double	ret;

	if (direction == LEFT || direction == RIGHT)
	{
		if (direction == LEFT)
			data->v.init_w -= data->speed;
		if (direction == RIGHT)
			data->v.init_w += data->speed;
		ret = data->minimap_size * (data->pos_x + data->v.init_w)
			+ data->v.center_w + wid_hei;
	}
	if (direction == UP || direction == DOWN)
	{
		if (direction == UP)
			data->v.init_h -= data->speed;
		if (direction == DOWN)
			data->v.init_h += data->speed;
		ret = data->minimap_size * (data->pos_y + data->v.init_h + 1)
			+ data->v.center_h + wid_hei;
	}
	return (ret);
}

void	zoom_player(t_data *data, double *pos_play, int h, int w)
{
	int	padding;

	padding = 5;
	while (pos_play[X] + padding * 10 >= data->width * 0.9)
		pos_play[X] = move_map(data, LEFT, w);
	while (pos_play[X] + w - padding * 10 <= data->width * 0.3)
		pos_play[X] = move_map(data, RIGHT, w);
	while (pos_play[Y] + padding * 10 >= data->height)
		pos_play[Y] = move_map(data, UP, h);
	while (pos_play[Y] - padding * 10 <= data->height * 0.7
		&& data->v.init_h <= -1)
		pos_play[Y] = move_map(data, DOWN, h);
}

int		is_off_limit(t_data *data, double *pos_play)
{
	if ((pos_play[Y] + 100 * data->speed <= data->height * 0.7)
		|| (pos_play[Y] + 100 * data->speed >= data->height)
		|| (pos_play[X] + 100 * data->speed <= data->width * 0.3)
		|| (pos_play[X] + 100 * data->speed >= data->width * 0.9))
		return (1);
	return (0);
}

void	set_color(t_data *data, int w, int h, double *pos_play)
{
	t_img_data	img;

	img = data->player;
	if (img.img_ptr)
		img.color = ((unsigned int *)img.img_infos)
		[img.width * (h - 1) + (w - 1)];
	if (img.color == 0x000000)
		img.color = 0x000001;
	if ((img.color & 0x00FFFFFF) != 0)
	{
		my_mlx_pixel_put(data, pos_play[X] + w - 0.5 * img.width,
			pos_play[Y] + h - 0.5 * img.height, img.color);
	}
}

void	set_player(t_data *data)
{
	int		w;
	int		h;
	double	pos_play[2];

	w = 0;
	h = 0;
	pos_play[X] = data->minimap_size * (data->pos_x + data->v.init_w)
		+ data->v.center_w;
	pos_play[Y] = data->minimap_size * (data->pos_y + data->v.init_h + 1)
		+ data->v.center_h;
	while (h++ < data->player.height)
	{
		while (w++ < data->player.width)
		{
			if (data->v.move == 1)
				zoom_player(data, pos_play, h, w);
			if (is_off_limit(data, pos_play) && !data->v.move)
				return ;
			set_color(data, w, h, pos_play);
		}
		w = 0;
	}
}
