#include "cub3d.h"

void	set_texture(t_data *data)
{
	if (data->side == SOUTH)
		while (data->t->side != 's')
			data->t = data->t->next;
	else if (data->side == WEST)
		while (data->t->side != 'w')
			data->t = data->t->next;
	else if (data->side == EAST)
		while (data->t->side != 'e')
			data->t = data->t->next;
	else if (data->side == NORTH)
		while (data->t->side != 'n')
			data->t = data->t->next;
}

void	calculate_wall(t_data *data, t_draw *d, int line_h)
{
	double	wallx;

	d->start_y = (-line_h / 2) + (data->height * data->look);
	if (d->start_y + data->jump < 0)
		d->start_y = 0 - data->jump;
	d->end_y = (line_h / 2) + (data->height * data->look);
	if (d->end_y + data->jump >= data->height)
		d->end_y = data->height - 1 - data->jump;
	if (data->side == WEST || data->side == EAST)
		wallx = data->pos_y + (data->perpwalldist * data->raydir_y);
	else
		wallx = data->pos_x + (data->perpwalldist * data->raydir_x);
	wallx -= floor(wallx);
	d->tex_x = (int)(wallx * (double)data->t->w);
	if ((data->side == EAST || (data->side == WEST)) && data->raydir_x > 0)
		d->tex_x = data->t->w - d->tex_x - 1;
	if ((data->side == NORTH || data->side == SOUTH) && data->raydir_y < 0)
		d->tex_x = data->t->w - d->tex_x - 1;
}

void	wall_drawing(t_data *data, int x)
{
	t_draw	d;
	int		line_h;
	double	step;
	double	t_pos;
	int		y;

	line_h = (int)(data->height / data->perpwalldist);
	calculate_wall(data, &d, line_h);
	step = (1.0 * data->t->h) / line_h;
	t_pos = (d.start_y - (data->height * data->look) + (line_h / 2)) * step;
	set_texture(data);
	d.start_y += data->jump;
	d.end_y += data->jump;
	y = d.start_y - 1;
	while (++y <= d.end_y)
	{
		d.tex_y = (int)t_pos & (data->t->h - 1);
		t_pos += step;
		data->color = ((unsigned int *)data->t->imgaddr)
		[data->t->h * d.tex_y + d.tex_x];
		my_mlx_pixel_put(data, x, y, data->color);
	}
}
