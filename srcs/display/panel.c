/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 15:02:28 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/26 15:03:30 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	strput(t_data *data, char *str, int pad)
{
	mlx_string_put(data->mlx, data->win, data->width * 0.1 + 5,
		data->height * 0.7 + pad, BLACK, str);
}

void	coordinates_display(t_data *data, int *n)
{
	char	*stringx;
	char	*stringy;
	char	*posx;
	char	*posy;

	posx = ft_ftoa(data->pos_x, 4);
	posy = ft_ftoa(data->pos_y, 4);
	stringx = ft_strjoin("X = ", posx);
	stringy = ft_strjoin("Y = ", posy);
	strput(data, stringx, *n += 15);
	strput(data, stringy, *n += 15);
	free(stringx);
	free(stringy);
	free(posx);
	free(posy);
}

void	display_pos(t_data *data)
{
	int	n;

	n = -2;
	strput(data, "Commands", n += 15);
	coordinates_display(data, &n);
	strput(data, "[ + / - ] Resize map ", n += 15);
	strput(data, "[ [] '| ] Move in map ", n += 15);
	strput(data, "[ <- -> ] Rotate player ", n += 15);
	strput(data, "[ WASD ] Move player ", n += 15);
	strput(data, "[ UP/DOWN ] Look up/down ", n += 15);
	strput(data, "[ H/J ] Squat / Jump ", n += 15);
	strput(data, "[ M ] Reset map ", n += 15);
	strput(data, "[ Space ] Hide ", n += 15);
	strput(data, "[ Esc ] Quit ", n += 15);
}
