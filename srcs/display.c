#include "cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->imgaddr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	if (x >= 0 && x < data->width && y >= 0 && y < data->height)
		*(unsigned int *)dst = color;
}

void fill_black(t_data *data)
{
	int i = 0;
	int j = 0;

	while (i < data->height - 1)
	{
		while (j < data->width - 1)
		{
			my_mlx_pixel_put(data, j, i, 0x000000);
			j++;
		}
		j = 0;
		i++;
	}
}

void fill_ceiling(t_data *data)
{
	int i = 0;
	int j = 0;

	while (i < data->height / 2)
	{
		while (j < data->width)
		{
			my_mlx_pixel_put(data, j, i, data->info->ceiling_rgb);
			j++;
		}
		j = 0;
		i++;
	}
}

void fill_floor(t_data *data)
{
	int i = data->height / 2;
	int j = 0;

	while (i < data->height)
	{
		while (j < data->width)
		{
			my_mlx_pixel_put(data, j, i, data->info->floor_rgb);
			j++;
		}
		j = 0;
		i++;
	}
}



void display(t_data *data)
{
	t_bresenham b;

	fill_black(data);
	fill_ceiling(data);
	fill_floor(data);
	dda(data);
	b.pt1[X] = data->pos_x * data->minimap_size + data->width / 4;
	b.pt1[Y] = data->pos_y * data->minimap_size + data->height * 0.7;
	b.pt2[X] = (data->pos_x + data->dirx) * data->minimap_size + data->width / 4;
	b.pt2[Y] = (data->pos_y + data->diry) * data->minimap_size + data->height * 0.7;
	if (data->displaymap == 1)
	{
		set_compass(data);
		set_map(data);
		set_player(data);
		data->color = 0xffffff;
		bresenham(&b, data);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	display_pos(data);
}
