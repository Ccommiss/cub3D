#include "cub3d.h"

/*
 *  free_textures & free_sprites
 *
 * 	[synopsis] : free textures and sprites
 * 	[return] : -1, because these functions are also used while parsing if
 * 		an allocation fails.
 */

int	free_textures(t_data *data, t_text *head)
{
	int		i;
	t_text	*tmp;

	if (data->t != head)
		data->t = head;
	i = 0;
	while (i < 4 && data->t != NULL)
	{
		tmp = data->t;
		data->t = data->t->next;
		if (tmp->img)
			mlx_destroy_image(data->mlx, tmp->img);
		free(tmp);
		tmp = NULL;
		i++;
	}
	return (-1);
}

int	free_sprites(t_data *data)
{
	t_spr	*tmp_s;

	tmp_s = data->spr->head;
	while (data->spr != NULL)
	{
		data->spr = tmp_s->next;
		free(tmp_s);
		tmp_s = data->spr;
	}
	return (-1);
}

void	free_info(t_data *data)
{
	if (data->info->north_text)
		free(data->info->north_text);
	if (data->info->south_text)
		free(data->info->south_text);
	if (data->info->east_text)
		free(data->info->east_text);
	if (data->info->west_text)
		free(data->info->west_text);
	if (data->info->sprite_text)
		free(data->info->sprite_text);
	if (data->sprimg)
		mlx_destroy_image(data->mlx, data->sprimg);
	if (data->compass.img_ptr)
		mlx_destroy_image(data->mlx, data->compass.img_ptr);
	if (data->map_icon.img_ptr)
		mlx_destroy_image(data->mlx, data->map_icon.img_ptr);
	if (data->player.img_ptr)
		mlx_destroy_image(data->mlx, data->player.img_ptr);
}

/*
 *  free_game
 *
 * 	[synopsis] : properly closes the window and free elements previously
 * 		allocated, e.g.
 * 		> The map (t_data structure)
 * 		> Textures (pointed by data->t)
 * 		> data->spr (data->sprite)
 * 		> The zbuffer
 * 	[return] : none
 */

int	free_game(t_data *data)
{
	int	i;

	i = 0;
	if (data->map)
	{
		while (i < data->map_h)
		{
			printf(":: %s \n", data->map[i]);
			free(data->map[i++]);
		}
		free(data->map);
	}
	if (data->t)
		free_textures(data, data->t);
	if (data->spr)
		free_sprites(data);
	if (data->zbuffer)
		free(data->zbuffer);
	free_info(data);
	return (0);
}

int	close_win(t_data *data)
{
	if (data->win)
	{
		mlx_clear_window(data->mlx, data->win);
		mlx_destroy_window(data->mlx, data->win);
	}
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	free_game(data);
	printf("exiting\n");
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);//linux
		free(data->mlx);
	}
	system("killall afplay"); //mac
	exit(1);
}
