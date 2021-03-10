#include "../includes/cub3d.h"


/*
 *  free_textures & free_sprites
 *
 * 	[synopsis] : free textures and sprites
 * 	[return] : -1, because these functions are also used while parsing if
 * 		an allocation fails.
 */


int free_textures(t_data *data, t_text *head)
{
	int i;
	t_text *tmp;

	if (data->t != head)
		data->t = head;
	i = 0;
	// FREE LES STR* STRDUPEES dans PARSE INFOS
	free(data->info->north_text);
	free(data->info->south_text);
	free(data->info->east_text);
	free(data->info->west_text);
	free(data->info->sprite_text);

	while (i < 4 && data->t != NULL) // FREE LES TEXTURES
	{
		tmp = data->t;
	 	data->t = data->t->next;
		printf ("FREEING %c \n", tmp->side);
		if (tmp->img) //si on a pas eu d'erreurs de chargement
			mlx_destroy_image(data->mlx, tmp->img);
		free(tmp);
		tmp = NULL;
		i++;
	}
	return (-1);
}

int free_sprites(t_data *data)
{
	t_spr *tmp_s;

	while (data->spr != NULL)
	{
		tmp_s = data->spr;
		data->spr = data->spr->next;
		printf ("deleting spr index %d \n", tmp_s->index);
		free(tmp_s);
	}
	if (data->sprimg)
		mlx_destroy_image(data->mlx, data->sprimg); //on free limage
	return (-1);
}

/*
 *  red_cross
 *
 * 	[synopsis] : properly closes the window and free elements previously
 * 		allocated, e.g.
 * 		> The map (t_data structure)
 * 		> Textures (pointed by data->t)
 * 		> data->spr (data->sprite)
 * 		> The zbuffer
 * 	[return] : none
 */

int free_game(t_data *data)
{
	int i;

	i = 0;
	while (i <= data->map_h)
	{
		printf(":: %s \n", data->map[i]);
		free(data->map[i++]);
	}
	free(data->map);
	free_textures(data, data->t);
	if (data->sprimg != NULL)
		free_sprites(data);
	free(data->zbuffer);
	printf ("coucou ici\n" );
	return (0);
}

int close_win(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img);
	free_game(data);
//	mlx_destroy_display(data->mlx);//linux
	free(data->mlx);
	exit(1);
}
