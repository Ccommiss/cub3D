#include "cub3d.h"

int is_zero(char c)
{
	if (c == '0') // || c == '2') et 2 sil faut traverser
		return (1);
	return (0);
}

void hit_check(t_data *data)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{

		if (data->dx < data->dy)
		{
			data->dx += data->delta_x;
			data->map_x += data->stepX;
			if (data->stepX < 0)
				data->side = WEST;
			else
				data->side = EAST;
		}
		else
		{
			data->dy += data->delta_y;
			data->map_y += data->stepY;
			if (data->stepY < 0)
				data->side = NORTH;
			else
				data->side = SOUTH;
		}
		if (data->map_x < 0)
			data->map_x = 0;
		if (data->map_y < 0)
			data->map_y = 0;

		if ((data->map_y < 0 || data->map_x < 0) 
			|| (data->map[data->map_y][data->map_x] == '1'))
			hit = 1;
	}
}

void calculate_step(t_data *data)
{
	if (data->raydir_x < 0)
	{
		data->stepX = -1;
		data->dx = (data->pos_x - data->map_x) * data->delta_x;
	}
	else
	{
		data->stepX = 1;
		data->dx = (data->map_x + 1.0 - data->pos_x) * data->delta_x;
	}
	if (data->raydir_y < 0)
	{
		data->stepY = -1;
		data->dy = (data->pos_y - data->map_y) * data->delta_y;
	}
	else
	{
		data->stepY = 1;
		data->dy = (data->map_y + 1.0 - data->pos_y) * data->delta_y;
	}
}

void calculate_wall(t_data *data, t_draw *d, int line_h)
{
	double wallx;

	d->start_y = (-line_h / 2) + (data->height / 2);
	if (d->start_y < 0)
		d->start_y = 0;
	d->end_y = (line_h / 2) + (data->height / 2);
	if (d->end_y >= data->height)
		d->end_y = data->height - 1;
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

void set_texture(t_data *data)
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

void draw(t_data *data, int x)
{
	t_draw d;
	int line_h;
	double step;
	double t_pos;
	int y;

	line_h = (int)(data->height / data->perpwalldist);
	calculate_wall(data, &d, line_h);
	step = (1.0 * data->t->h) / line_h;
	t_pos = (d.start_y - (data->height / 2) + (line_h / 2)) * step;
	set_texture(data);
	y = d.start_y - 1;
	while (++y < d.end_y)
	{
		d.tex_y = (int)t_pos & (data->t->h - 1);
		t_pos += step;
		data->color = ((unsigned int *)data->t->imgaddr)
			[data->t->h * d.tex_y + d.tex_x];
		my_mlx_pixel_put(data, x, y, data->color);
	}
}

void dda(t_data *data)
{
	int x;

	x = -1;
	while (++x < data->width)
	{
		data->camera_x = 2 * x / (double)data->width - 1;
		data->raydir_x = data->dirx + (data->planeX * data->camera_x);
		data->raydir_y = data->diry + (data->planeY * data->camera_x);
		data->map_x = (int)data->pos_x;
		data->map_y = (int)data->pos_y;
		data->delta_x = fabs(1 / data->raydir_x);
		data->delta_y = fabs(1 / data->raydir_y);
		calculate_step(data);
		hit_check(data);
		if (data->side == WEST || data->side == EAST)
			data->perpwalldist = (data->map_x - data->pos_x + (1 - data->stepX) / 2) / data->raydir_x;
		else
			data->perpwalldist = (data->map_y - data->pos_y + (1 - data->stepY) / 2) / data->raydir_y;
		draw(data, x);
		data->zbuffer[x] = data->perpwalldist;
	}
	if (data->spr != NULL)
	{
		sprite_casting(data);
		sprite_drawing(data);
	}
}
