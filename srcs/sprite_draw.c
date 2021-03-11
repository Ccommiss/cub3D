/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 11:01:14 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/11 11:58:35 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	compute_data(t_data *data, t_spr_geo *sp, t_draw *draw)
{
	sp->x = (data->spr->x + 0.5) - data->pos_x;
	sp->y = (data->spr->y + 0.5) - data->pos_y;
	sp->inv = 1.0 / (data->planeX * data->diry - data->dirx * data->planeY);
	sp->trans_x = sp->inv * (data->diry * sp->x - data->dirx * sp->y);
	sp->trans_y = sp->inv * ((-data->planeY * sp->x) + (data->planeX * sp->y));
	sp->screen_x = (int)((data->width / 2) * (1 + sp->trans_x / sp->trans_y));
	sp->height = abs((int)(data->height / (sp->trans_y)));
	sp->width = abs((int)(data->height / (sp->trans_y)));
	draw->start_y = -sp->height / 2 + data->height / 2;
	if (draw->start_y < 0)
		draw->start_y = 0;
	draw->end_y = sp->height / 2 + data->height / 2;
	if (draw->end_y >= data->height)
		draw->end_y = data->height - 1;
	draw->start_x = -sp->width / 2 + sp->screen_x - 1;
	if (draw->start_x < 0)
		draw->start_x = 0;
	draw->end_x = sp->width / 2 + sp->screen_x;
	if (draw->end_x >= data->width)
		draw->end_x = data->width - 1;
}

void	draw_text(t_data *data, t_draw *draw, t_spr_geo *sp)
{
	int d;

	d = (draw->y) * 256 - data->height * 128 + sp->height * 128;
	draw->tex_y = ((d * data->sph) / sp->height) / 256;
	draw->color = ((unsigned int *)data->sprimgaddr)
	[data->spw * draw->tex_y + draw->tex_x];
	if ((draw->color & 0x00FFFFFF) != 0)
		my_mlx_pixel_put(data, draw->start_x, draw->y, draw->color);
}

void	sprite_drawing(t_data *data)
{
	t_spr		*head;
	t_spr_geo	sp;
	t_draw		draw;

	head = data->spr->head;
	while (data->spr != NULL)
	{
		compute_data(data, &sp, &draw);
		while (++draw.start_x < draw.end_x)
		{
			draw.tex_x = (int)(256 * (draw.start_x -
			(-sp.width / 2 + sp.screen_x)) * data->spw / sp.width) / 256;
			if (sp.trans_y > 0 && draw.start_x > 0
				&& draw.start_x < data->width
					&& sp.trans_y <= data->zbuffer[draw.start_x])
			{
				draw.y = draw.start_y - 1;
				while (++draw.y < draw.end_y)
					draw_text(data, &draw, &sp);
			}
		}
		data->spr = data->spr->next;
	}
	data->spr = head;
}
