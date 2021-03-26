#include "cub3d.h"

// POur boussole et carte

void	init_compass(t_data *data)
{
	data->compass.img_ptr = mlx_xpm_file_to_image(data->mlx,
			"pics/compass_S.xpm", &data->compass.width, &data->compass.height);
	if (data->compass.img_ptr)
		data->compass.img_infos = mlx_get_data_addr(data->compass.img_ptr,
				&data->compass.bpp, &data->compass.sl, &data->compass.endian);
	data->map_icon.img_ptr = mlx_xpm_file_to_image(data->mlx, "pics/map.xpm",
			&data->map_icon.width, &data->map_icon.height);
	if (data->map_icon.img_ptr)
		data->map_icon.img_infos = mlx_get_data_addr(data->map_icon.img_ptr,
				&data->map_icon.bpp, &data->map_icon.sl,
				&data->map_icon.endian);
	data->player.img_ptr = mlx_xpm_file_to_image(data->mlx, "pics/yoshi.xpm",
			&data->player.width, &data->player.height);
	if (!data->player.img_ptr)
	{
		data->player.width = 5;
		data->player.height = 5;
		data->player.color = RED;
	}
	if (data->player.img_ptr)
		data->player.img_infos = mlx_get_data_addr(data->player.img_ptr,
				&data->player.bpp, &data->player.sl, &data->player.endian);
}

/*
**  set_needle
**
** 	[synopsis] :
** 		> sets the needle of the compass
**		> pt1 is departure, pt2 is arrival
**	[call] : in set_compass
** 	[return] : none
*/

void	set_needle(t_data *data)
{
	t_bresenham	b;
	t_img_data	i;

	i = data->compass;
	data->color = RED;
	b.pt1[X] = i.width / 2;
	b.pt1[Y] = i.height / 2 - 4;
	b.pt2[X] = (i.width / 2) + data->dirx * 40;
	b.pt2[Y] = (i.height / 2 - 4) + data->diry * 40;
	bresenham(&b, data);
	b.pt1[Y] += 1;
	b.pt2[Y] += 1;
	bresenham(&b, data);
}

void	set_compass(t_data *data)
{
	t_img_data	i;
	int			x;
	int			y;

	x = 0;
	y = 0;
	i = data->compass;
	if (!i.img_ptr)
		return ;
	while (y < i.height)
	{
		while (x < i.width)
		{
			data->color = ((unsigned int *)i.img_infos)[i.width * y + x];
			if (data->color == 0x000000)
				data->color = 0x000001;
			if ((data->color & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(data, x, y, data->color);
			x++;
		}
		x = 0;
		y++;
	}
	set_needle(data);
}

void	set_mapicon(t_data *data)
{
	t_img_data	i;
	int			x;
	int			y;

	x = 0;
	y = 0;
	i = data->map_icon;
	if (!i.img_ptr)
		return ;
	while (y < i.height)
	{
		while (x < i.width)
		{
			i.color = ((unsigned int *)i.img_infos)[i.width * y + x];
			if (i.color == 0x000000)
				i.color = 0x000001;
			if ((i.color & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(data, x + 20, y + data->height * 0.9, i.color);
			x++;
		}
		x = 0;
		y++;
	}
}
