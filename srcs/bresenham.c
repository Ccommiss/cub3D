#include "cub3d.h"

void	bsnhm_1(t_bresenham *b, t_data *data)
{
	float			a;
	int				temp;
	unsigned int	x;

	x = 0;
	a = 0;
	temp = 0;
	if (b->pt1[X] > b->pt2[X])
	{
		temp = b->pt1[X];
		b->pt1[X] = b->pt2[X];
		b->pt2[X] = temp;
		temp = b->pt1[Y];
		b->pt1[Y] = b->pt2[Y];
		b->pt2[Y] = temp;
	}
	a = ((float)(b->pt2[Y] - b->pt1[Y]) / (b->pt2[X] - b->pt1[X]));
	while (x++ < b->dx + 1)
		my_mlx_pixel_put(data, x + b->pt1[X], b->pt1[Y] + (x * a), data->color);
}

void	bsnhm_2(t_bresenham *b, t_data *data)
{
	float			a;
	int				temp;
	unsigned int	y;

	y = 0;
	a = 0;
	temp = 0;
	if (b->pt1[Y] > b->pt2[Y])
	{
		temp = b->pt1[Y];
		b->pt1[Y] = b->pt2[Y];
		b->pt2[Y] = temp;
		temp = b->pt1[X];
		b->pt1[X] = b->pt2[X];
		b->pt2[X] = temp;
	}
	a = ((float)(b->pt2[X] - b->pt1[X]) / (b->pt2[Y] - b->pt1[Y]));
	while (y++ < b->dy + 1)
		my_mlx_pixel_put(data, b->pt1[X] + (y * a), y + b->pt1[Y], data->color);
}

void	bsnhm_3(t_bresenham *b, t_data *data)
{
	float	a;
	int		temp;
	int		y;

	y = 0;
	a = 0;
	temp = 0;
	if (b->pt1[Y] > b->pt2[Y])
	{
		temp = b->pt1[Y];
		b->pt1[Y] = b->pt2[Y];
		b->pt2[Y] = temp;
	}
	y = b->pt1[Y];
	while (y++ < b->pt2[Y] + 1)
		my_mlx_pixel_put(data, b->pt1[X], y, data->color);
}

void	bsnhm_4(t_bresenham *b, t_data *data)
{
	float	a;
	int		temp;
	int		x;

	x = 0;
	a = 0;
	temp = 0;
	if (b->pt1[X] > b->pt2[X])
	{
		temp = b->pt1[X];
		b->pt1[X] = b->pt2[X];
		b->pt2[X] = temp;
	}
	x = b->pt1[X];
	while (x++ < b->pt2[X] + 1)
		my_mlx_pixel_put(data, x, b->pt1[Y], data->color);
}

void	bresenham(t_bresenham *b, t_data *data)
{
	b->dx = abs(b->pt2[X] - b->pt1[X]);
	b->dy = abs(b->pt2[Y] - b->pt1[Y]);
	if (b->dx >= b->dy && b->dx != 0 && b->dy != 0)
		bsnhm_1(b, data);
	if (b->dx < b->dy && b->dx != 0 && b->dy != 0)
		bsnhm_2(b, data);
	if (b->dx == 0)
		bsnhm_3(b, data);
	if (b->dy == 0)
		bsnhm_4(b, data);
}
