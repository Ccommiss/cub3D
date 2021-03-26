/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 15:13:55 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/26 15:14:05 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	zoom_minimap(int keycode, t_data *data)
{
	if (keycode == KEY_PLUS)
	{
		if (data->minimap_size < data->width / 20)
			data->minimap_size++;
		data->v.center_w = (data->width / 2 - (data->minimap_size
					* data->map_w / 2));
		data->v.center_h = data->height * 0.7;
		data->v.move = 2;
	}
	if (keycode == KEY_MINUS)
	{
		if (data->minimap_size * data->map_w > 0.9 * data->width
			|| data->minimap_size * data->map_h > 0.2 * data->height)
			data->minimap_size--;
		data->v.center_w = (data->width / 2 - (data->minimap_size
					* data->map_w / 2));
		data->v.center_h = data->height * 0.7;
		data->v.move = 2;
	}
}

void	move_inmap(int keycode, t_data *data)
{
	if (keycode == KEY_BRACE_L)
	{
		if ((data->minimap_size * data->map_w > 0.7 * data->width
				|| data->minimap_size * data->map_h > 0.3 * data->height)
			&& (data->v.init_w < data->map_w / 2))
			data->v.init_w += 1;
	}
	if (keycode == KEY_BRACE_R)
	{
		if ((data->minimap_size * data->map_w > 0.7 * data->width
				|| data->minimap_size * data->map_h > 0.3 * data->height)
			&& (data->v.init_w > -1))
			data->v.init_w -= 1;
	}
	if (keycode == KEY_SINGLEQUOT)
	{
		if (data->v.init_h + (data->map_h - 1) >= 0)
			data->v.init_h -= 1;
	}
	if (keycode == KEY_BACKSLASH)
	{
		if (data->v.init_h < data->map_h - 1)
			data->v.init_h += 1;
	}
}

void	minimap_settings(int keycode, t_data *data)
{
	zoom_minimap(keycode, data);
	move_inmap(keycode, data);
	if (keycode == KEY_SPACE)
	{
		if (data->displaymap == 0)
			data->displaymap = 1;
		else
			data->displaymap = 0;
	}
	if (keycode == KEY_M)
		init_minimap(data);
}
