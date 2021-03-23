#include "cub3d.h"

int	is_zero(char c)
{
	if (c == '0')
		return (1);
	return (0);
}

void	hit_check(t_data *data)
{
	data->hit = 0;
	while (data->hit == 0)
	{
		if (data->dx < data->dy)
		{
			data->dx += data->delta_x;
			data->map_x += data->stepx;
			if (data->stepx < 0)
				data->side = WEST;
			else
				data->side = EAST;
		}
		else
		{
			data->dy += data->delta_y;
			data->map_y += data->stepy;
			if (data->stepy < 0)
				data->side = NORTH;
			else
				data->side = SOUTH;
		}
		if (data->map[data->map_y][data->map_x] == '1')
			data->hit = 1;
	}
}

void calculate_step(t_data *data)
{
	if (data->raydir_x < 0)
	{
		data->stepx = -1;
		data->dx = (data->pos_x - data->map_x) * data->delta_x;
	}
	else
	{
		data->stepx = 1;
		data->dx = (data->map_x + 1.0 - data->pos_x) * data->delta_x;
	}
	if (data->raydir_y < 0)
	{
		data->stepy = -1;
		data->dy = (data->pos_y - data->map_y) * data->delta_y;
	}
	else
	{
		data->stepy = 1;
		data->dy = (data->map_y + 1.0 - data->pos_y) * data->delta_y;
	}
}

void calculate_wall(t_data *data, t_draw *d, int line_h)
{
	double wallx;

	d->start_y = (-line_h / 2) + (data->height * data->look) ; //tesstt
	if (d->start_y + data->jump < 0) //test
		d->start_y = 0;
	d->end_y = (line_h / 2) + (data->height * data->look); //testt
	if (d->end_y + data->jump >= data->height)
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
	t_pos = (d.start_y - (data->height * data->look) + (line_h / 2)) * step; ///test
	set_texture(data);

	d.start_y += data->jump ; //test
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

void dda(t_data *data)
{
	int x;

	x = 0;
	while (x < data->width)
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
			data->perpwalldist = (data->map_x - data->pos_x + (1 - data->stepx) / 2) / data->raydir_x;
		else
			data->perpwalldist = (data->map_y - data->pos_y + (1 - data->stepy) / 2) / data->raydir_y;
		draw(data, x);
		data->zbuffer[x] = data->perpwalldist;
		x++;
	}
	if (data->spr != NULL)
	{
		data->spr = data->spr->head;
		sprite_casting(data);
		sprite_drawing(data);
	}
}
