/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 15:09:04 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/26 15:09:06 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_sprite_info(t_data *data)
{
	data->sprimg = mlx_xpm_file_to_image(data->mlx, data->info->sprite_text,
			&data->spw, &data->sph);
	if (!data->sprimg)
		return (error_message(data, TEXTURE_NOT_FOUND));
	data->sprimgaddr = mlx_get_data_addr(data->sprimg, &data->sprbpx,
			&data->spline, &data->end);
	return (1);
}

/*
**  alloc_image
**
** 	[synopsis] :
** 		> Alloc textures specified in the .cub file for walls
**		> Perform a circular linked list where side 'e' points on
**			side 'n'
** 	[return] : exits and free all previous allocated images
**			and others if an allocation fails
*/

int	alloc_image(t_data *data, t_text *t, void *text)
{
	t->img = mlx_xpm_file_to_image(data->mlx, text, &t->w, &t->h);
	if (!t->img)
	{
		t->next = NULL;
		return (error_message(data, TEXTURE_NOT_FOUND));
	}
	t->imgaddr = mlx_get_data_addr(t->img, &t->bits_per_pixel,
			&t->line_length, &t->endian);
	if (text != data->info->east_text)
	{
		t->next = (t_text *)malloc(sizeof(t_text));
		if (!t->next)
			return (error_message(data, MALLOC_ERROR));
		t->next->next = NULL;
	}
	return (1);
}

int	loadimage(t_data *data)
{
	t_text	*t;
	t_text	*head;

	t = (t_text *)malloc(sizeof(t_text));
	if (!t)
		return (error_message(data, MALLOC_ERROR));
	head = t;
	data->t = head;
	t->side = 'n';
	alloc_image(data, t, data->info->north_text);
	t = t->next;
	t->side = 's';
	alloc_image(data, t, data->info->south_text);
	t = t->next;
	t->side = 'w';
	alloc_image(data, t, data->info->west_text);
	t = t->next;
	t->side = 'e';
	alloc_image(data, t, data->info->east_text);
	t->next = head;
	load_sprite_info(data);
	return (1);
}
