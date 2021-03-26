/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 15:14:19 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/26 15:14:20 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_leftright(int keycode, t_data *data, int sec_spd, int sec_oth)
{
	if (keycode == KEY_A)
	{
		if (is_zero(data->map[(int)(data->pos_y)]
			[(int)(data->pos_x + data->diry * (data->speed + sec_spd))]))
			data->pos_x += data->diry * data->speed;
		if (is_zero(data->map[(int)(data->pos_y - data->dirx
				* (data->speed + sec_spd))][(int)(data->pos_x + sec_oth)])
				&& is_zero(data->map[(int)(data->pos_y - data->dirx
				* (data->speed + sec_spd))]
			[(int)(data->pos_x - sec_oth)]))
			data->pos_y -= data->dirx * data->speed;
	}
	if (keycode == KEY_D)
	{
		if (is_zero(data->map[(int)(data->pos_y)]
			[(int)(data->pos_x - data->diry * (data->speed + sec_spd))]))
			data->pos_x -= data->diry * data->speed;
		if (is_zero(data->map[(int)(data->pos_y + data->dirx
				* (data->speed + sec_spd))][(int)(data->pos_x + sec_oth)])
				&& is_zero(data->map[(int)(data->pos_y + data->dirx
				* (data->speed + sec_spd))]
			[(int)(data->pos_x - sec_oth)]))
			data->pos_y += data->dirx * data->speed;
	}
}

void	move_updown(int keycode, t_data *data, int sec_spd, int sec_oth)
{
	if (keycode == KEY_W)
	{
		if (is_zero(data->map[(int)(data->pos_y)]
			[(int)(data->pos_x + data->dirx * (data->speed + sec_spd))]))
			data->pos_x += data->dirx * data->speed;
		if (is_zero(data->map[(int)(data->pos_y + data->diry
				* (data->speed + 0.1))][(int)(data->pos_x - sec_oth)])
			&& is_zero(data->map[(int)(data->pos_y + data->diry
				* (data->speed + 0.1))]
			[(int)(data->pos_x + sec_oth)]))
			data->pos_y += data->diry * data->speed;
	}
	if (keycode == KEY_S)
	{
		if (is_zero(data->map[(int)(data->pos_y)]
			[(int)(data->pos_x - data->dirx * (data->speed + 0.1))]))
			data->pos_x -= data->dirx * data->speed;
		if (is_zero(data->map[(int)(data->pos_y - data->diry
				* (data->speed + sec_spd))][(int)(data->pos_x - sec_oth)])
			&& is_zero(data->map[(int)(data->pos_y - data->diry
				* (data->speed + sec_spd))]
			[(int)(data->pos_x + sec_oth)]))
			data->pos_y -= data->diry * data->speed;
	}
}
