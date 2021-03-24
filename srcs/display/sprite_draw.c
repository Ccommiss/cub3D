
#include "cub3d.h"

/*
**	compute_data
**
**	[synopsis] : compute sprite height, width, transformation on both axis,
** 				 and pixels to be drawn
**	[call] : sprite_drawing, for each sprite to be drawn
**	[return] : none
*/

void	compute_data(t_data *data, t_spr_geo *sp, t_draw *draw)
{
	sp->x = (data->spr->x + 0.5) - data->pos_x;
	sp->y = (data->spr->y + 0.5) - data->pos_y ;
	sp->inv = 1.0 / (data->planeX * data->diry - data->dirx * data->planeY);
	sp->trans_x = sp->inv * (data->diry * sp->x - data->dirx * sp->y);
	sp->trans_y = sp->inv * ((-data->planeY * sp->x) + (data->planeX * sp->y));
	sp->screen_x = (int)((data->width / 2) * (1 + sp->trans_x / sp->trans_y));
	sp->height = abs((int)(data->height / (sp->trans_y)));
	sp->width = abs((int)(data->height  / (sp->trans_y)));

	draw->start_y = -sp->height * 0.5 + (data->height) * (data->look);
	if (draw->start_y + data->jump <= 0)
		draw->start_y = - 1 - data->jump; // yessss

	draw->end_y = sp->height * 0.5 + (data->height) * (data->look) ;
	if (draw->end_y + data->jump >= data->height) // a regle un pb
		draw->end_y = data->height;

	draw->start_x = -sp->width / 2 + sp->screen_x - 1;
	if (draw->start_x <= 0)
		draw->start_x = -1;
	draw->end_x = sp->width / 2 + sp->screen_x;
	if (draw->end_x >= data->width)
		draw->end_x = data->width;
}

/*
**	draw_text
**
** 	[synopsis] : draws texture column by column
** 				 and pixels to be drawn
**  [call] : sprite_drawing, for each sprite column to be drawn
**	[return] : none
*/

void	draw_text(t_data *data, t_draw *draw, t_spr_geo *sp)
{
	int d;

	d = ((draw->y - data->jump) * 256 - ((data->height) * 256 * data->look) + (sp->height * 128));
	draw->tex_y = (abs)((d * data->sph) / sp->height) / 256;
	if (data->spw * draw->tex_y + draw->tex_x > 63 * 63 || data->spw * draw->tex_y + draw->tex_x < 0)
	{
		return ;
	}
	draw->color = ((unsigned int *)data->sprimgaddr)
	[data->spw * draw->tex_y + draw->tex_x];
	if ((draw->color & 0x00FFFFFF) != 0)
		my_mlx_pixel_put(data, draw->start_x, draw->y, draw->color);
}

/*
**	sprite_drawing
**
** 	[synopsis] : draws sprites
**  [call] : in dda (raycasting)
**	[return] : none
*/

void	sprite_drawing(t_data *data)
{
	t_spr		*head;
	t_spr_geo	sp;
	t_draw		draw;

	head = data->spr->head;
	while (data->spr != NULL)
	{
		compute_data(data, &sp, &draw);
		draw.start_y += data->jump;
		draw.end_y += data->jump;
		while (++draw.start_x < draw.end_x)
		{

			draw.tex_x = (int)(256 * (draw.start_x -
			(-sp.width / 2 + sp.screen_x)) * data->spw / sp.width) / 256;
			if (sp.trans_y > 0 && draw.start_x >= 0
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
