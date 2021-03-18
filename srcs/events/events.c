/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:18:12 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/18 16:56:51 by ccommiss         ###   ########.fr       */
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

	if (keycode == KEY_SHIFT)
		data->speed = 0.20;

	if (keycode == KEY_W)
	{
		if (is_zero(data->map[(int)(data->pos_y)][(int)(data->pos_x + data->dirx * (data->speed + 0.02))]))
			data->pos_x += data->dirx * data->speed;
		if (is_zero(data->map[(int)(data->pos_y + data->diry * (data->speed + 0.02))][(int)(data->pos_x)]))
			data->pos_y += data->diry * data->speed;
	}
	if (keycode == KEY_S)
	{
		printf ("::%c \n", data->map[(int)(data->pos_y)][(int)(data->pos_x - data->dirx * (data->speed + 0.02))]);
		if (is_zero(data->map[(int)(data->pos_y)][(int)(data->pos_x - data->dirx * (data->speed + 0.02))]))
			data->pos_x -= data->dirx * data->speed;
		if (is_zero(data->map[(int)(data->pos_y - data->diry * (data->speed + 0.02))][(int)(data->pos_x)]))
			data->pos_y -= data->diry * data->speed;
		printf ("apres mvt X ::%c \n", data->map[(int)(data->pos_y)][(int)(data->pos_x)]);
		printf ("apres mvt X ::%d %d \n", (int)(data->pos_y), (int)(data->pos_x));
	}
	if (keycode == KEY_A)
	{
		if (is_zero(data->map[(int)(data->pos_y)][(int)(data->pos_x + data->diry * (data->speed + 0.02))]))
			data->pos_x += data->diry * data->speed;
		if (is_zero(data->map[(int)(data->pos_y - data->dirx * (data->speed + 0.02))][(int)(data->pos_x)]))
		 	data->pos_y -= data->dirx * data->speed;
	}
	if (keycode == KEY_D)
	{
		if (is_zero(data->map[(int)(data->pos_y)][(int)(data->pos_x - data->diry * (data->speed + 0.02))]))
			data->pos_x -= data->diry * data->speed;
		if (is_zero(data->map[(int)(data->pos_y + data->dirx * (data->speed + 0.02))][(int)(data->pos_x)]))
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
	if (keycode == KEY_SPACE)
	{
		if (data->displaymap == 0)
			data->displaymap = 1;
		else
			data->displaymap = 0;
	}
	if (keycode == KEY_ESC)
		close_win(data);
	display(data);
	return (1);
}
