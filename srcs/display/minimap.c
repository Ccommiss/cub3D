#include "cub3d.h"

/*
**  items_color
**
** 	[synopsis] :
** 		> draw each item as a square according to its type
**	[call] : in set_map
** 	[return] : none
*/

void	items_color(t_data *data, t_visu2d *v)
{
	if (v->pixw >= 0.9 * data->width || v->pixw <= 0.3 * data->width
		|| v->pixh >= data->height || v->pixh <= data->height * 0.7)
		return ;
	if (data->map[v->h][v->w] == '1' && v->pixw % (rand() % 3 + v->pixw) != 0)
		my_mlx_pixel_put(data, v->pixw, v->pixh, GREY);
	else if (data->map[v->h][v->w] == '1')
		my_mlx_pixel_put(data, v->pixw, v->pixh, LIGHTGREY);
	else if (data->map[v->h][v->w] == '2')
		my_mlx_pixel_put(data, v->pixw, v->pixh, YELLOW);
	else if (data->map[v->h][v->w] == '0')
		my_mlx_pixel_put(data, v->pixw, v->pixh, GRASS);
}

/*
**  map_background
**
** 	[synopsis] :
** 		> fills map background in yellow and vintage yellow
**	[call] : in set_map
** 	[return] : none
*/

void	map_background(t_data *data)
{
	int	i;
	int	j;

	i = data->height * 0.7 - 5;
	j = data->width * 0.1 - 8;
	srand(42);
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

void	set_map(t_data *data)
{
	t_visu2d	v;

	v.w = -1;
	v.h = -1;
	v.pixw = 0;
	v.pixh = 0;
	map_background(data);
	while (++v.h < data->map_h)
	{
		while (++v.w < data->map_w)
		{
			v.pixh = data->minimap_size
				* (v.h + data->v.init_h + 1) + data->v.center_h;
			while (v.pixh++ < (data->minimap_size * (v.h + data->v.init_h + 2)
					+ data->v.center_h))
			{
				v.pixw = data->minimap_size * (v.w + data->v.init_w)
					+ data->v.center_w;
				while (v.pixw++ < data->minimap_size
					* (v.w + 1 + data->v.init_w) + data->v.center_w)
					items_color(data, &v);
			}
		}
		v.w = -1;
	}
}
