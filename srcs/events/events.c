/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:18:12 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/25 12:42:03 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	actions_values(int keycode, t_data *data)
{
	if (keycode == KEY_SHIFT)
		data->speed = 0.20;
	if (keycode == KEY_J)
		data->jump = 250;
	if (keycode == KEY_H)
		data->jump = -250;
	if (keycode == KEY_UP && data->look < 0.9)
		data->look += 0.1;
	if (keycode == KEY_DOWN && data->look > 0)
		data->look -= 0.1;
}

void	move_hook(int keycode, t_data *data)
{
	double	sec_spd;
	double	sec_oth;

	sec_spd = 0.01;
	sec_oth = 0.001;
	move_leftright(keycode, data, sec_spd, sec_oth);
	move_updown(keycode, data, sec_spd, sec_oth);
}

/*
**  look_hook
**
** 	[synopsis] : changes value in order to look up/down/
**					right/left
**	[call] : in key_hook
** 	[return] : none
*/

void	dir_hook(int keycode, t_data *data)
{
	double	olddirx;
	double	oldplanex;

	if (keycode == KEY_RIGHT)
	{
		olddirx = data->dirx;
		data->dirx = data->dirx * cos(0.2 + data->speed) - data->diry
			* sin(0.2 + data->speed);
		data->diry = olddirx * sin(0.2 + data->speed) + data->diry
			* cos(0.2 + data->speed);
		oldplanex = data->planeX;
		data->planeX = data->planeX * cos(0.2 + data->speed) - data->planeY
			* sin(0.2 + data->speed);
		data->planeY = oldplanex * sin(0.2 + data->speed) + data->planeY
			* cos(0.2 + data->speed);
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
}

int	speed_hook(int keycode, t_data *data)
{
	if (keycode == KEY_SHIFT)
		data->speed = 0.11;
	if (keycode == KEY_J || keycode == KEY_H)
	{
		data->jump = 0;
		display(data);
	}
	return (1);
}

int	key_hook(int keycode, t_data *data)
{
	move_hook(keycode, data);
	dir_hook(keycode, data);
	actions_values(keycode, data);
	minimap_settings(keycode, data);
	if (keycode == KEY_ESC)
		close_win(data);
	display(data);
	return (1);
}
