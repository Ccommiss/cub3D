#include "cub3d.h"

void bresenham(int xdep, int ydep, int xfin, int yfin, t_data *data)
{
	float a = 0;
	int temp = 0;
	int cste = 0;

	unsigned int dy;
	unsigned int dx;

	dx = abs(xfin - xdep);
	dy = abs(yfin - ydep);
	if (dx >= dy && dx != 0 && dy != 0)
	{
		if (xdep > xfin)
		{
			temp = xdep;
			xdep = xfin;
			xfin = temp;

			temp = ydep;
			ydep = yfin;
			yfin = temp;
		}
		a = ((float)(yfin - ydep) / (xfin - xdep));

		for (unsigned int x = 0; x < dx + 1; x++)
		{
			my_mlx_pixel_put(data, x + xdep, ydep + (x * a) + cste, data->color);
		}
	}

	if (dx < dy && dx != 0 && dy != 0)
	{
		if (ydep > yfin)
		{
			temp = ydep;
			ydep = yfin;
			yfin = temp;

			temp = xdep;
			xdep = xfin;
			xfin = temp;
		}
		a = ((float)(xfin - xdep) / (yfin - ydep));

		for (unsigned int y = 0; y < dy + 1; y++)
		{
			my_mlx_pixel_put(data, xdep + (y * a) + cste, y + ydep, data->color);
		}
	}

	if (dx == 0)
	{
		if (ydep > yfin)
		{
			temp = ydep;
			ydep = yfin;
			yfin = temp;
		}
		for (int y = ydep; y < yfin + 1; y++)
			my_mlx_pixel_put(data, xdep, y, data->color);
	}
	if (dy == 0)
	{
		if (xdep > xfin)
		{
			temp = xdep;
			xdep = xfin;
			xfin = temp;
		}
		for (int x = xdep; x < xfin + 1; x++)
			my_mlx_pixel_put(data, x, ydep, data->color);
	}
}
