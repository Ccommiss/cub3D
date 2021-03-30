/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:58:26 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/30 11:53:54 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_zero(char c, t_data *data)
{
	if (c == '2' && data->lifebar.lives > 0)
		data->lifebar.lives -= 1;
	if (c == '0')
		return (1);
	return (0);
}

/*
**  hit_check : the Digital differential analyzer
**
** 	[synopsis] :
** 		> if dx > dy i.e difference between x1 and x2 is bigger
**			than beetween y1 and y2, we follow dx slope, and increments
**			it, and see which one is bigger next, until the
**			map position reached by consecutives moves is a 1, i.e.
**			a wall.
**	[call] : in wall_casting
** 	[return] : none
*/

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

void	calculate_step(t_data *data)
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

/*
**  perpendicular_ray
**
** 	[synopsis] : to avoid fisheye effect, a perpendicular
**		ray from camera plane to the hit wall.
**	[call] : in wall_casting
** 	[return] : none
**
**       ^         ^		 ^ |
**        \        |        /  |
**         \       |       /   |
**          \      |      /    |
**           \     |     /     |
**            \    |    /      |
**             \   |   /     perpwalldist
**              \  |  /      to avoid fisheye
**               \ | /         |
**                \|/          |
**        player (._.)		   |
**				  /|\		   |
**				  / \<---------+
**<------------------------------------->
**                               camera plane
*/

void	perpendicular_ray(t_data *data)
{
	if (data->side == WEST || data->side == EAST)
		data->perpwalldist = (data->map_x - data->pos_x
				+ (1 - data->stepx) / 2) / data->raydir_x;
	else
		data->perpwalldist = (data->map_y - data->pos_y
				+ (1 - data->stepy) / 2) / data->raydir_y;
}

void	wall_casting(t_data *data)
{
	int	x;

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
		perpendicular_ray(data);
		wall_drawing(data, x);
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
