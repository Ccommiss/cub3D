
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
	mlx_string_put(data->mlx, data->win, data->width * 0.1 + 5, data->height * 0.7 + 20, BLACK, "Commands");
	mlx_string_put(data->mlx, data->win, data->width * 0.1 + 5, data->height * 0.7 + 35, BLACK, stringX);
	mlx_string_put(data->mlx, data->win, data->width * 0.1 + 5, data->height * 0.7 + 50, BLACK, stringY);
	mlx_string_put(data->mlx, data->win, data->width * 0.1 + 5, data->height * 0.7 + 65, BLACK, "[ + / - ] Resize map ");
	mlx_string_put(data->mlx, data->win, data->width * 0.1 + 5, data->height * 0.7 + 80, BLACK, "[ [] '| ] Move in map ");
	mlx_string_put(data->mlx, data->win, data->width * 0.1 + 5, data->height * 0.7 + 95, BLACK, "[ <- -> ] Rotate player ");
	mlx_string_put(data->mlx, data->win, data->width * 0.1 + 5, data->height * 0.7 + 110, BLACK, "[ WASD ] Move player ");
	mlx_string_put(data->mlx, data->win, data->width * 0.1 + 5, data->height * 0.7 + 125 , BLACK, "[ Space ] Hide ");
	mlx_string_put(data->mlx, data->win, data->width * 0.1 + 5, data->height * 0.7 + 140 , BLACK, "[ Esc ] Quit ");

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
	int x_play = data->minimap_size * (data->pos_x + data->v.init_w) + data->v.center_w;
	int y_play = data->minimap_size * (data->pos_y + data->v.init_h + 1) + data->v.center_h;

	int move;
	move = data->v.move;

	s_play = data->minimap_size / 5;
	if (s_play < 5)
		s_play = 5;

	while (h++ < s_play)
	{
		while (w++ < s_play)
		{
			x_play = data->minimap_size * (data->pos_x + data->v.init_w) + data->v.center_w + w;
			y_play = data->minimap_size * (data->pos_y + data->v.init_h + 1) + data->v.center_h + h;
			while (x_play + w + s_play * 10 >= data->width * 0.9 && move)
			{
				data->v.init_w -= data->speed;
				x_play = data->minimap_size * (data->pos_x + data->v.init_w) + data->v.center_w + w;
			}
			while (x_play + w - s_play * 10  <= data->width * 0.3 && move)
			{
				data->v.init_w += data->speed;
				x_play = data->minimap_size * (data->pos_x + data->v.init_w) + data->v.center_w + w;
			}
			while (y_play + s_play * 10  >= data->height && move)
			{
				data->v.init_h -= data->speed;
				y_play = data->minimap_size * (data->pos_y + data->v.init_h + 1) + data->v.center_h + h;

			}
			while (y_play - s_play * 10  <= data->height * 0.7 && move && data->v.init_h <= -1)
			{
				data->v.init_h += data->speed;
				y_play = data->minimap_size * (data->pos_y + data->v.init_h + 1) + data->v.center_h + h;
			}
			if (((data->minimap_size * (data->pos_y + data->v.init_h + 1) + h  + data->v.center_h - s_play <= data->height * 0.7)
			|| (data->minimap_size * (data->pos_y + data->v.init_h + 1) + h  + data->v.center_h + s_play  >= data->height)
			|| (data->minimap_size * (data->pos_x + data->v.init_w) + w  + data->v.center_w - s_play  <= data->width * 0.3)
			|| (data->minimap_size * (data->pos_x + data->v.init_w) + w  + data->v.center_w + s_play >= data->width * 0.9)) && !move)
				return (0);

			my_mlx_pixel_put(data, (data->minimap_size * (data->pos_x + data->v.init_w)  + data->v.center_w + w ),
							 ( data->minimap_size * (data->pos_y + data->v.init_h + 1) + h  + data->v.center_h), BLUE);
		}
		w = 0;
	}
	return (0);
}

void items_color(t_data *data, t_visu2d *v)
{
	if (v->pixw >= 0.9 * data->width || v->pixw <= 0.3 * data->width
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


void fill_map(t_data *data)
{
	int i;
	int j;

	i = data->height * 0.7 - 5;
	j = data->width * 0.1 - 8;
	while (i < data->height - 1)
	{
		while (j < data->width * 0.9 + 5)
		{
			if (rand() % 3 != 0 && j >= data->width * 0.1)
				my_mlx_pixel_put(data, j, i, YELLOW);
			else if (j >= data->width * 0.1)
				my_mlx_pixel_put(data, j, i, VINTAGE_YELLOW);
			else if (j <= data->width * 0.1 && rand() % 6 != 0)
				my_mlx_pixel_put(data, j, i, VINTAGE_YELLOW);
			j++;
		}
		j = data->width * 0.1 - 5;
		i++;
	}
}


void set_map(t_data *data)
{
 	t_visu2d v;

	v.w = -1 ;
	v.h = -1 ;
	v.pixw = 0;
	v.pixh = 0;

	srand(42);
	fill_map(data);
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
			//data->v.init_w += data->pos_x;
		}
		v.w = -1;
		//data->v.init_h += data->pos_y;
	}
	t_bresenham b;
	b.pt1[X] = data->width * 0.1 - 1;
	b.pt1[Y] = data->height * 0.7;
	b.pt2[X] = data->width * 0.9 + 1;
	b.pt2[Y] = data->height * 0.7;
	data->color = WHITE;
	bresenham (&b, data);
}





void set_mapicon(t_data *data)
{
	int endian;
	int bpp;
	int w;
	int h;
	int sl;


	void *img = mlx_xpm_file_to_image(data->mlx, "pics/map.xpm", &w, &h);
	if (!img)
		return ;
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
				my_mlx_pixel_put(data, x + 20, y + data->height * 0.9, color);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_destroy_image(data->mlx, img);

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
