#include "cub3d.h"


int key_hook(int keycode, t_data *data)
{
	if (keycode == KEY_UP)
	{
		if (checkzero_letter(data->map[(int)(data->pos_y)][(int)(data->pos_x + data->dirX * 0.11)]))
			data->pos_x += data->dirX * 0.10;
		if (checkzero_letter(data->map[(int)(data->pos_y + data->dirY * 0.11)][(int)(data->pos_x)]))
			data->pos_y += data->dirY * 0.10;
	}
	if (keycode == KEY_DOWN)
	{
		if (checkzero_letter(data->map[(int)(data->pos_y)][(int)(data->pos_x - data->dirX * 0.11)]))
			data->pos_x -= data->dirX * 0.10;
		if (checkzero_letter(data->map[(int)(data->pos_y - data->dirY * 0.11)][(int)(data->pos_x)]))
			data->pos_y -= data->dirY * 0.10;
	}
	if (keycode == KEY_RIGHT) //ROTATION A FAIRE
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = data->dirX;
		data->dirX = data->dirX * cos(0.2) - data->dirY * sin(0.2);
		data->dirY = oldDirX * sin(0.2) + data->dirY * cos(0.2);

		double oldPlaneX = data->planeX;
		data->planeX = data->planeX * cos(0.2) - data->planeY * sin(0.2);
		data->planeY = oldPlaneX * sin(0.2) + data->planeY * cos(0.2);
	}
	if (keycode == KEY_LEFT)
	{
		double oldDirX = data->dirX;
		data->dirX = data->dirX * cos(-0.2) - data->dirY * sin(-0.2);
		data->dirY = oldDirX * sin(-0.2) + data->dirY * cos(-0.2);
		double oldPlaneX = data->planeX;
		data->planeX = data->planeX * cos(-0.2) - data->planeY * sin(-0.2);
		data->planeY = oldPlaneX * sin(-0.2) + data->planeY * cos(-0.2);
	}
	if (keycode == KEY_SPACE)
	{
		if (data->displaymap == 0)
			data->displaymap = 1;
		else
			data->displaymap = 0;
	}
	if (keycode == KEY_S)
		data->cameraY -= 0.10;
	if (keycode == KEY_W)
		data->cameraY += 0.10;
	display(data);
	return (1);
}
