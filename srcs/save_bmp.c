/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:05:44 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/06 10:47:45 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	fill_header(t_data *data, int fd)
{
	t_bmp info;

	write(fd, "BM", 2);
	info.bmfh_size = 54 + (4 * data->width * data->height);
	write(fd, &info.bmfh_size, 4);
	write(fd, "\0\0\0\0", 4);
	info.bmfh_offset = 54;
	write(fd, &info.bmfh_offset, 4);
	info.bmih_size = 40;
	write(fd, &info.bmih_size, 4);
	info.bmih_w = data->width;
	write(fd, &info.bmih_w, 4);
	info.bmih_h = data->height;
	write(fd, &info.bmih_h, 4);
	info.bmih_plane = 1;
	write(fd, &info.bmih_plane, 2);
	info.bmih_bpp = data->bits_per_pixel;
	write(fd, &info.bmih_bpp, 2);
	info.bmih_compression = 0;
	write(fd, &info.bmih_compression, 4);
	write(fd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 20);
}

void	fill_core(t_data *data, int fd)
{
	int				x;
	int				y;
	unsigned int	color;

	x = 0;
	y = data->height - 1;
	color = 0;
	while (y >= 0)
	{
		while (x < data->width)
		{
			color = ((unsigned int *)data->imgaddr)[(y * data->width) + x++];
			write(fd, &color, 3);
			write(fd, "\0", 1);
		}
		x = 0;
		y--;
	}
}

void	save_bmp(t_data *data)
{
	int fd;

	fill_black(data);
	fill_ceiling(data);
	fill_floor(data);
	dda(data);
	fd = open("save.bmp", O_CREAT | O_WRONLY);
	fill_header(data, fd);
	fill_core(data, fd);
}
