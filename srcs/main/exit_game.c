#include "cub3d.h"

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

	printf("Texture la\n");

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
		printf("FREEING %c \n", tmp->side);
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

	printf("sprites la\n");
	
	tmp_s = data->spr->head;
	while (data->spr != NULL)
	{
		data->spr = tmp_s->next;
		printf("deleting spr index %d \n", tmp_s->index);
		free(tmp_s);
		tmp_s = data->spr;
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
	if (data->map)
	{
			//while (data->map[i] != NULL)
		while (i < data->map_h) //verifier que ca fait pas des leaks
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
	return (0);
}

int close_win(t_data *data)
{
	checkmap(data);
	if (data->win)
	{
		mlx_clear_window(data->mlx, data->win);
		mlx_destroy_window(data->mlx, data->win);
	}
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	free_game(data);
	printf("exiting\n");
//	mlx_destroy_display(data->mlx);//linux
	if (data->mlx)
		free(data->mlx);
	exit(1);
}
