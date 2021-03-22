/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu2d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:14:55 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/22 13:37:20 by ccommiss         ###   ########.fr       */
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
	int s_play;

	s_play = data->minimap_size / 5;
	if (s_play < 5)
		s_play = 5;
	while (h++ < s_play)
	{
		while (w++ < s_play)
			my_mlx_pixel_put(data, (data->minimap_size * (data->pos_x + data->v.init_w) + w  + data->v.center_w),
							 ( data->minimap_size * (data->pos_y + data->v.init_h + 1) + h  + data->v.center_h), BLUE);
		w = 0;
	}
	return (0);
}

void items_color(t_data *data, t_visu2d *v)
{
	if (v->pixw >= 0.9 * data->width || v->pixw <= 0.1 * data->width
	|| v->pixh >= data->height || v->pixh <= data->height * 0.7)
		return;
	if (data->map[v->h][v->w] == '1' && v->pixw % (rand() % 3 + v->pixw) != 0)
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

	v.w = -1 ;
	v.h = -1 ;
	v.pixw = 0;
	v.pixh = 0;
	srand(42);
	while (++v.h < data->map_h)
	{
		while (++v.w < data->map_w)
		{

			v.pixh = data->minimap_size * (v.h + data->v.init_h + 1) + data->v.center_h;
			while (v.pixh++ < (data->minimap_size * (v.h + data->v.init_h + 1 + 1) + data->v.center_h))
			{
				v.pixw = data->minimap_size * (v.w + data->v.init_w ) + data->v.center_w;
				while (v.pixw++ < data->minimap_size * (v.w + 1 + data->v.init_w) + data->v.center_w)
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
