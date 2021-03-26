#include "cub3d.h"

/*
 *  init_plane
 *
 * 	[synopsis] : initialises planeX and planeY according to direction.
 * 			Camera plane must be perpendicular to direction.
 * 			FOV (field of view) is here initialized at 66 deg.
 * 	[return] : none
 */

void	init_plane(t_data *data)
{
	if (data->dirx == -1 || data->dirx == 1)
		data->planeX = 0;
	else if (data->dirx == 0 && data->diry == -1)
		data->planeX = 0.66;
	else if (data->dirx == 0 && data->diry == 1)
		data->planeX = -0.66;
	if (data->diry == -1 || data->diry == 1)
		data->planeY = 0;
	else if (data->diry == 0 && data->dirx == -1)
		data->planeY = -0.66;
	else if (data->diry == 0 && data->dirx == 1)
		data->planeY = 0.66;
}

void 	init_minimap(t_data *data)
{
	data->v.init_h = -1;
	data->v.init_w = -1;
	data->minimap_size = data->width / 50;
	while (data->minimap_size * data->map_h > 0.3 * data->height)
		data->minimap_size--;
	while (data->minimap_size * data->map_w > 0.7 * data->width)
		data->minimap_size--;
	data->v.center_w = (data->width / 2 - (data->minimap_size
				* data->map_w / 2));
	data->v.center_h = data->height * 0.7;
	init_compass(data);
}

/*
 *  init_struct
 *
 * 	[synopsis] :
 * 		> init mlx lib, window, image
 * 		> init plane of camera after dir has been set during parsing
 * 		> set minimap size and activates its displaying by default
 * 		> malloc the z buffer later used for displaying textures
 * 	[return] : none
 */

int	init_struct(t_data *data)
{
	loadimage(data);
	data->win = mlx_new_window(data->mlx, data->width, data->height, "Cub3D");
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	data->imgaddr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	init_plane(data);
	while (ft_isempty(data->map[data->map_h - 1]))
	{
		free(data->map[data->map_h - 1]);
		data->map_h--;
	}
	init_minimap(data);
	data->displaymap = 1;
	data->zbuffer = (double *)malloc(sizeof(double) * (data->width + 1));
	if (!data->zbuffer)
		error_message(data, MALLOC_ERROR);
	ft_bzero(data->zbuffer, data->width);
	return (1);
}

void 	init_infos(t_data *data)
{
	data->info->ceiling_rgb = -1;
	data->info->floor_rgb = -1;
	data->info->north_text = NULL;
	data->info->south_text = NULL;
	data->info->east_text = NULL;
	data->info->west_text = NULL;
	data->info->sprite_text = NULL;
	data->compass.img_ptr = NULL;
	data->map_icon.img_ptr = NULL;
	data->player.img_ptr = NULL;
}

/*
 *  init_base
 *
 * 	[synopsis] :
 * 		> init some useful variables later modified by parser
 * 		> Helps to handle errors detection
 * 	[return] : none
 */

void	init_base(t_data *data)
{
	data->mlx = mlx_init();
	data->img = NULL;
	data->win = NULL;
	data->width = 0;
	data->height = 0;
	data->error = 0;
	data->pos_x = -1;
	data->pos_y = -1;
	data->speed = 0.10;
	data->map = NULL;
	data->map_h = 0;
	data->map_w = 0;
	data->spr = NULL;
	data->sprimg = NULL;
	data->t = NULL;
	data->zbuffer = NULL;
	data->v.init_w = -1;
	data->v.init_h = -1;
	data->v.move = 0;
	data->look = 0.5;
	data->jump = 0;
	init_infos(data);
}
