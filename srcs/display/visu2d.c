/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu2d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:14:55 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/18 15:54:53 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void checkmap(t_data *data)
{
	printf("W : [%d] H : [%d]\n", data->map_w, data->map_h);
	int i;
	int j;
	for (i = 0; i < data->map_h; i++)
	{
		for (j = 0; j < data->map_w; j++)
		{
			printf("[%d][%d]", i, j);
			printf("%c ", data->map[i][j]);
		}
		printf("\n");
	}
}

void display_pos(t_data *data)
{
	char *stringX;
	char *stringY;
	char *posx;
	char *posy;

	posx = ft_ftoa(data->pos_x, 4);
	posy = ft_ftoa(data->pos_y, 4);
	stringX = ft_strjoin("X = ", posx);
	stringY = ft_strjoin("Y = ", posy);
	mlx_string_put(data->mlx, data->win, 30, data->height - 50, BLUE, stringX);
	mlx_string_put(data->mlx, data->win, 30, data->height - 25, BLUE, stringY);
	free(stringX);
	free(stringY);
	free(posx);
	free(posy);
}

int set_player(t_data *data)
{
	int w = 0;
	int h = 0;

	while (h++ < 3)
	{
		while (w++ < 3)
			my_mlx_pixel_put(data, (data->pos_x * data->minimap_size + w + data->v.center_w),
							 (data->pos_y * data->minimap_size + h + data->v.center_h), BLUE);
		w = 0;
	}
	return (0);
}

void items_color(t_data *data, t_visu2d *v)
{
	if (data->map[v->h][v->w] == '1' && (v->pixw) % (rand() % 3 + v->pixw) != 0)
		my_mlx_pixel_put(data, v->pixw, v->pixh, GREY);
	else if (data->map[v->h][v->w] == '1')
		my_mlx_pixel_put(data, v->pixw, v->pixh, LIGHTGREY);
	else if (data->map[v->h][v->w] == '2')
		my_mlx_pixel_put(data, v->pixw, v->pixh, YELLOW);
	else if (data->map[v->h][v->w] == '0')
		my_mlx_pixel_put(data, v->pixw, v->pixh, GRASS);
}

void set_map(t_data *data)
{
 	t_visu2d v;

	v.w = -1;
	v.h = -1;
	v.pixw = 0;
	v.pixh = 0;
	srand(42);
	while (++v.h < data->map_h)
	{
		while (++v.w < data->map_w)
		{
			v.pixh = data->minimap_size * v.h + data->height * 0.7;
			while (v.pixh++ < (data->minimap_size * (v.h + 1) + data->height * 0.7) - 1)
			{
				v.pixw = data->minimap_size * (v.w) + 
				(data->width / 2 - (data->minimap_size * data->map_w / 2));
				while (v.pixw++ < (data->minimap_size * (v.w + 1) - 1) + 
				(data->width / 2 - (data->minimap_size * data->map_w / 2))) 
					items_color(data, &v);
			}
		}
		v.w = -1;
	}
}

void set_compass(t_data *data)
{
	int endian;
	int bpp;
	int w;
	int h;
	int sl;

	t_bresenham b;

	void *img = mlx_xpm_file_to_image(data->mlx, "pics/compass_S.xpm", &w, &h);
	void *imginfo = mlx_get_data_addr(img, &bpp, &sl, &endian);

	int x = 0;
	int y = 0;
	int color;

	while (y < h)
	{
		while (x < w)
		{
			color = ((unsigned int *)imginfo)[w * y + x];
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
	b.pt1[X] = w / 2;						  //xdep
	b.pt1[Y] = h / 2 - 4;					  //ydep
	b.pt2[X] = (w / 2) + data->dirx * 40;	  //xfin
	b.pt2[Y] = (h / 2 - 4) + data->diry * 40; //yfin
	bresenham(&b, data);
	b.pt1[Y] += 1; //ydep
	b.pt2[Y] += 1;
	bresenham(&b, data);
	mlx_destroy_image(data->mlx, img);
	img = NULL;
}
