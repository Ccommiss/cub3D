#include "../includes/cub3d.h"


int key_hook(int keycode, t_data *data)
{
	double olddirx;
	double oldplanex;

	if (keycode == KEY_W)
	{
		if (checkzero_letter(data->map[(int)(data->pos_y)][(int)(data->pos_x + data->dirx * 0.11)]))
			data->pos_x += data->dirx * 0.10;
		if (checkzero_letter(data->map[(int)(data->pos_y + data->diry * 0.11)][(int)(data->pos_x)]))
			data->pos_y += data->diry * 0.10;
	}
	if (keycode == KEY_S)
	{
		if (checkzero_letter(data->map[(int)(data->pos_y)][(int)(data->pos_x - data->dirx * 0.11)]))
			data->pos_x -= data->dirx * 0.10;
		if (checkzero_letter(data->map[(int)(data->pos_y - data->diry * 0.11)][(int)(data->pos_x)]))
			data->pos_y -= data->diry * 0.10;
	}
	if (keycode == KEY_D) 
	{
		olddirx = data->dirx;
		data->dirx = data->dirx * cos(0.2) - data->diry * sin(0.2);
		data->diry = olddirx * sin(0.2) + data->diry * cos(0.2);
		oldplanex = data->planeX;
		data->planeX = data->planeX * cos(0.2) - data->planeY * sin(0.2);
		data->planeY = oldplanex * sin(0.2) + data->planeY * cos(0.2);
	}
	if (keycode == KEY_A)
	{
		olddirx = data->dirx;
		data->dirx = data->dirx * cos(-0.2) - data->diry * sin(-0.2);
		data->diry = olddirx * sin(-0.2) + data->diry * cos(-0.2);
		oldplanex = data->planeX;
		data->planeX = data->planeX * cos(-0.2) - data->planeY * sin(-0.2);
		data->planeY = oldplanex * sin(-0.2) + data->planeY * cos(-0.2);
	}
	if (keycode == KEY_SPACE)
	{
		if (data->displaymap == 0)
			data->displaymap = 1;
		else
			data->displaymap = 0;
	}
	if (keycode == KEY_S)
		data->camera_y -= 0.10;
	if (keycode == KEY_W)
		data->camera_y += 0.10;
	display(data);
	return (1);
}
