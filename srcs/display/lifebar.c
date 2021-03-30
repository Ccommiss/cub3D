/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifebar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:24:33 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/30 15:28:22 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	background_lifebar(t_data *data, int s)
{
	int w;
	int h;

	w = 0;
	h = 0;
	while (h < s + 2)
	{
		w = 0.5 * data->width - 10;
		while (w++ < s * 5 + 0.5 * data->width + 8)
			my_mlx_pixel_put(data, w - 0.5 * 5 * s, h, WHITE);
		h++;
	}
}

void	draw_lifebar(t_data *data)
{
	int i;
	int pixw;
	int pixh;
	int s;

	i = 0;
	pixh = 0;
	s = data->width / 20;
	pixw = 0.5 * data->width;
	background_lifebar(data, s);
	while (i < data->lifebar.lives)
	{
		while (pixh < s)
		{
			pixw = 0.5 * data->width + i * s;
			while (pixw++ < (s + 0.5 * data->width + i * s) - 2)
				my_mlx_pixel_put(data, pixw - 0.5 * 5 * s, pixh, RED);
			pixh++;
		}
		i++;
		pixh = 0;
	}
}
