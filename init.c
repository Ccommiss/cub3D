#include "cub3d.h"

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
	if (data->dirX == -1 || data->dirX == 1)
		data->planeX = 0;
	else if (data->dirX == 0 && data->dirY == -1)
		data->planeX = 0.66;
	else if (data->dirX == 0 && data->dirY == 1)
		data->planeX = -0.66;
	if (data->dirY == -1 || data->dirY == 1)
		data->planeY = 0;
	else if (data->dirY == 0 && data->dirX == -1)
		data->planeY = -0.66;
	else if (data->dirY == 0 && data->dirX == 1)
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
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->width, data->height, "who run the world ?");
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	data->imgaddr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	init_plane(data);
	data->minimap_size = data->width / 50;
	data->displaymap = 1;
	data->zbuffer = (double *)malloc(sizeof(double) * (data->width + 1));
	ft_bzero(data->zbuffer, data->width);
	if (loadimage(data) == -1)
		return(-1);
	return (1);
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
		printf ("YO \n");
		t->next = (t_text *)malloc(sizeof(t_text));
	}
	return (1);
}

int loadimage(t_data *data)
{
	t_text *t;
	t_text *head;

	t = (t_text *)malloc(sizeof(t_text));
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
	data->sprimg = mlx_xpm_file_to_image(data->mlx, data->info->sprite_text, &data->spw, &data->sph);
	data->sprimgaddr = mlx_get_data_addr(data->sprimg, &data->sprbpx, &data->spline, &data->end);
	return (1);
}

