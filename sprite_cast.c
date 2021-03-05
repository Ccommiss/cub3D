/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_cast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 11:02:02 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/05 14:00:44 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	swap(t_spr *tmp, t_spr *tmp_next)
{
	t_spr val_tmp;

	val_tmp.x = tmp->x;
	val_tmp.y = tmp->y;
	val_tmp.distance = tmp->distance;
	tmp->x = tmp_next->x;
	tmp->y = tmp_next->y;
	tmp->distance = tmp_next->distance;
	tmp_next->x = val_tmp.x;
	tmp_next->y = val_tmp.y;
	tmp_next->distance = val_tmp.distance;
}

t_spr	*sort_sprites(t_data *data, t_spr *head)
{
	t_spr *tmp;
	t_spr *tmp_next;

	tmp = data->spr;
	tmp_next = data->spr->next;
	while (tmp_next != NULL)
	{
		while (tmp_next != tmp)
		{
			if (tmp_next->distance > tmp->distance)
				swap(tmp, tmp_next);
			tmp = tmp->next;
		}
		tmp = head;
		tmp_next = tmp_next->next;
	}
	return (tmp);
}

void	sprite_casting(t_data *data)
{
	t_spr *head;

	printf ("SPRITE CASTING l\n");
	printf ("SPRITE CASTING 1 %p \n", data->spr->head);

	head = data->spr->head;

	while (data->spr != NULL)
	{
		data->spr->distance = (pow((data->pos_x - data->spr->x), 2)
		+ pow((data->pos_y - data->spr->y), 2));
		data->spr = data->spr->next;
			printf ("END 0 \n");

	}
	data->spr = head;
	printf ("END 1 \n");

	data->spr = sort_sprites(data, head);
	data->spr = head;
		printf ("END \n");

}
