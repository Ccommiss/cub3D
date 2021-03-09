#include "../includes/cub3d.h"



void checkmap(t_data *data)
{
	printf("W : [%d] H : [%d]\n", data->map_w, data->map_h);
	int i;
	int j;
	for (i = 0; i < data->map_h; i++)
	{
		for (j = 0; j < data->map_w; j++)
		{
			//printf("[%d][%d]\n", data->map_w, data->map_h);
			printf("[%d][%d]", i, j);
			printf("%c ", data->map[i][j]);
		}
		printf("\n");
	}
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

int set_player(t_data *data)
{
	int w = 0;
	int h = 0;

	while (h++ < 3)
	{
		while (w++ < 3)
			my_mlx_pixel_put(data, (data->pos_x * data->minimap_size + w + data->width / 4), (data->pos_y * data->minimap_size + h + data->height * 0.7), BLUE);
		w = 0;
	}
	return (0);
}

void set_map(t_data *data)
{
	int w;
	int h;
	int pixw;
	int pixh;

	w = 0;
	h = 0;
	pixw = 0;
	pixh = 0;

	while (h < data->map_h)
	{
		while (w < data->map_w)
		{
			if (checkzero_letter(data->map[h][w]) == 0)
			{
				pixh = data->minimap_size * h + data->height * 0.7; // data->height pour centrer
				while (pixh++ < data->minimap_size * (h + 1) + data->height * 0.7)
				{
					pixw = data->minimap_size * (w) + (data->width / 4);

					while (pixw++ < data->minimap_size * (w + 1) + (data->width / 4)) //pour mettre au milieu
					{
						if (data->map[h][w] == '1')
							my_mlx_pixel_put(data, pixw, pixh, 0xffd700);
						if (data->map[h][w] == '2')
							my_mlx_pixel_put(data, pixw, pixh, 0xffffff);
					}
				}
			}
			w++;
		}
		h++;
		w = 0;
	}
}

void set_compass(t_data *data)
{
	int endian;
	int bpp;
	int w;
	int h;
	int sl;

	void *img = mlx_xpm_file_to_image(data->mlx, "pics/compass_S.xpm", &w, &h);
	void *imginfo = mlx_get_data_addr(img, &bpp, &sl, &endian);

	int x = 0;
	int y = 0;
	int color;

	while (y < h)
	{
		while (x < w)
		{
			color = ((unsigned int *)imginfo)[w*y + x];
			//printf ("compass");
			if (color == 0x000000)
				color = 0x000001;
			if ((color & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
	data->color = RED;
	bresenham(w/2, h/2 - 4, (w/2) + data->dirx * 40, (h/2 - 4) + data->diry * 40, data);
	bresenham(w/2, h/2 - 3, (w/2) + data->dirx * 40, (h/2 - 3) + data->diry * 40, data);
	free(img);
	img = NULL;
}
