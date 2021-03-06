#include "cub3d.h"

/// FREE TO DO IN CASE OF ERROR


/*
 *  init_plane
 *
 * 	[synopsis] : initialises planeX and planeY according to direction.
 * 			Camera plane must be perpendicular to direction.
 * 			FOV (field of view) is here initialized at 66 deg.
 * 	[return] : none
 */

void init_plane(t_data *data)
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

int init_struct(t_data *data)
{
	if (loadimage(data) == -1)
		return (-1);
	data->win = mlx_new_window(data->mlx, data->width, data->height, "Cub3D");
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	data->imgaddr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	init_plane(data);
	data->minimap_size = data->width / 50;
	data->displaymap = 1;
	data->zbuffer = (double *)malloc(sizeof(double) * (data->width + 1));
	if (!data->zbuffer)
		{ //free des trucs
			return (-1);
		}
	ft_bzero(data->zbuffer, data->width);
	return (1);
}

/*
 *  init_base
 *
 * 	[synopsis] :
 * 		> init some useful variables later modified by parser
 * 		> Helps to handle errors detection
 * 	[return] : none
 */

void init_base(t_data *data)
{
	data->mlx = mlx_init();
	data->error = 0;
	data->pos_x = -1;
	data->pos_y = -1;
	data->speed = 0.10;
	data->info->ceiling_rgb = -1;
	data->info->floor_rgb = -1;
	data->map = NULL;
	data->map_h = 0;
	data->map_w = 0;
	data->spr = NULL;
	data->sprimg = NULL;
	data->t = NULL;
	data->info->north_text = NULL;
	data->info->south_text = NULL;
	data->info->east_text = NULL;
	data->info->west_text = NULL;
	data->info->sprite_text = NULL;
	data->zbuffer = NULL;

}

/*
 *  load image & alloc image
 *
 * 	[synopsis] :
 * 		> load textures specified in the .cub file for walls
 * 	[return] : none
 */

int	alloc_image(t_data *data, t_text *t, void *text)
{
	t->img = mlx_xpm_file_to_image(data->mlx, text, &t->w, &t->h);
	if (!t->img)
		return (error_message(data, 6));
	t->imgaddr = mlx_get_data_addr(t->img, &t->bits_per_pixel, &t->line_length, &t->endian);
	if (text != data->info->east_text)
	{
		t->next = (t_text *)malloc(sizeof(t_text));
		if (!t->next)
			return (-1);
	}
	return (1);
}

int loadimage(t_data *data)
{
	t_text *t;
	t_text *head;

	// les textures
	t = (t_text *)malloc(sizeof(t_text));
	if (!t)
		return (-1);
	head = t;
	t->side = 'n';
	if (alloc_image(data, t, data->info->north_text) == -1)
		return (-1);
	t = t->next;
	t->side = 's';
	if (alloc_image(data, t, data->info->south_text) == -1)
		return (-1);
	t = t->next;
	t->side = 'w';
	if (alloc_image(data, t, data->info->west_text) == -1)
		return (-1);
	t = t->next;
	t->side = 'e';
	if (alloc_image(data, t, data->info->east_text) == -1)
		return (-1);
	t->next = head;
	data->t = head;
	// ensuite on fait les sprites
	data->sprimg = mlx_xpm_file_to_image(data->mlx, data->info->sprite_text, &data->spw, &data->sph);
	data->sprimgaddr = mlx_get_data_addr(data->sprimg, &data->sprbpx, &data->spline, &data->end);
	return (1);
}

