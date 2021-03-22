/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:18:12 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/22 13:40:47 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



int speed_hook(int keycode, t_data *data)
{
	if (keycode == KEY_SHIFT)
		data->speed = 0.11;
	return 1;
}

int key_hook(int keycode, t_data *data)
{
	double olddirx;
	double oldplanex;
	double sec_spd; //security for speed
	double sec_oth; //sec for other case


	sec_spd = 0.01;
	sec_oth = 0.001;

	if (keycode == KEY_SHIFT)
		data->speed = 0.20;

	if (keycode == KEY_W)
	{
		if (is_zero(data->map[(int)(data->pos_y)][(int)(data->pos_x + data->dirx * (data->speed + sec_spd))]))
			data->pos_x += data->dirx * data->speed;
		if (is_zero(data->map[(int)(data->pos_y + data->diry * (data->speed + 0.1))][(int)(data->pos_x - sec_oth)])
		&& is_zero(data->map[(int)(data->pos_y + data->diry * (data->speed + 0.1))][(int)(data->pos_x + sec_oth)]))
			data->pos_y += data->diry * data->speed;
	}
	if (keycode == KEY_S)
	{
		if (is_zero(data->map[(int)(data->pos_y)][(int)(data->pos_x - data->dirx * (data->speed + 0.1))]))
			data->pos_x -= data->dirx * data->speed;
		if (is_zero(data->map[(int)(data->pos_y - data->diry * (data->speed + sec_spd))][(int)(data->pos_x - sec_oth)])
		&& is_zero(data->map[(int)(data->pos_y - data->diry * (data->speed + sec_spd))][(int)(data->pos_x + sec_oth)]))
			data->pos_y -= data->diry * data->speed;
	}
	if (keycode == KEY_A)
	{
		if (is_zero(data->map[(int)(data->pos_y)][(int)(data->pos_x + data->diry * (data->speed + sec_spd))]))
			data->pos_x += data->diry * data->speed;
		if (is_zero(data->map[(int)(data->pos_y - data->dirx * (data->speed + sec_spd))][(int)(data->pos_x + sec_oth)])
		&& is_zero(data->map[(int)(data->pos_y - data->dirx * (data->speed + sec_spd))][(int)(data->pos_x - sec_oth)]))
		 	data->pos_y -= data->dirx * data->speed;
	}
	if (keycode == KEY_D)
	{
		if (is_zero(data->map[(int)(data->pos_y)][(int)(data->pos_x - data->diry * (data->speed + sec_spd))]))
			data->pos_x -= data->diry * data->speed;
		if (is_zero(data->map[(int)(data->pos_y + data->dirx * (data->speed + sec_spd))][(int)(data->pos_x + sec_oth)])
		&& is_zero(data->map[(int)(data->pos_y + data->dirx * (data->speed + sec_spd))][(int)(data->pos_x - sec_oth)]))
		 	data->pos_y += data->dirx * data->speed;
	}
	if (keycode == KEY_RIGHT)
	{
		olddirx = data->dirx;
		data->dirx = data->dirx * cos(0.2 + data->speed) - data->diry * sin(0.2 + data->speed);
		data->diry = olddirx * sin(0.2 + data->speed) + data->diry * cos(0.2 + data->speed);
		oldplanex = data->planeX;
		data->planeX = data->planeX * cos(0.2 + data->speed) - data->planeY * sin(0.2 + data->speed);
		data->planeY = oldplanex * sin(0.2 + data->speed) + data->planeY * cos(0.2 + data->speed);
	}
	if (keycode == KEY_LEFT)
	{
		olddirx = data->dirx;
		data->dirx = data->dirx * cos(-0.2) - data->diry * sin(-0.2);
		data->diry = olddirx * sin(-0.2) + data->diry * cos(-0.2);
		oldplanex = data->planeX;
		data->planeX = data->planeX * cos(-0.2) - data->planeY * sin(-0.2);
		data->planeY = oldplanex * sin(-0.2) + data->planeY * cos(-0.2);
	}
	printf ("%d \n\n", keycode);
	if (keycode == KEY_PLUS)
	{
		if (data->minimap_size < data->width/ 20)
			data->minimap_size++;
		data->v.center_w = (data->width / 2 - (data->minimap_size * data->map_w / 2));
		data->v.center_h = data->height * 0.7;
	}
	if (keycode == KEY_MINUS) //minus
	{
		if (data->minimap_size > 10)
			data->minimap_size--;
		data->v.center_w = (data->width / 2 - (data->minimap_size * data->map_w / 2));
		data->v.center_h = data->height * 0.7;
	}
	if (keycode == KEY_SPACE)
	{
		if (data->displaymap == 0)
			data->displaymap = 1;
		else
			data->displaymap = 0;
	}
	if (keycode == KEY_BRACE_L)
	{
		if (data->v.init_w < data->map_w/2)
		data->v.init_w += 1;
	}
	if (keycode == KEY_BRACE_R)
	{
		if (data->v.init_w > -1)
			data->v.init_w -= 1;
	}
	if (keycode ==  KEY_SINGLEQUOT )
	{
	//	if (data->v.init_h > -1)
			data->v.init_h -= 1;
	}
	if (keycode ==  KEY_BACKSLASH )
	{
		//if (data->v.init_h < data->map_h/2)
			data->v.init_h += 1;
	}
	if (keycode ==  KEY_M )
		init_minimap(data);
	// if (data->pos_x / (double)((int)data->pos_x) != 1.00)
	// 	data->pos_x += 0.1;
	if (keycode == KEY_ESC)
		close_win(data);
	display(data);
	return (1);
}
