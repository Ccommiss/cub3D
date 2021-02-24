#include "cub3d.h"

int checkzero_letter(char c)
{
	if (c == '0') // || c == '2') //et 2 sil faut traverser
		return (1);
	return 0;
}




void perform_dda(t_data *data)
{
	int hit = 0;
	while (hit == 0)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		if (data->dx < data->dy)
		{
			data->dx += data->delta_x;
			data->mapX += data->stepX;
			if (data->stepX < 0)
				data->side = WEST;
			else
				data->side = EAST;
		}
		else
		{
			data->dy += data->delta_y;
			data->mapY += data->stepY;
			if (data->stepY < 0)
				data->side = NORTH;
			else
				data->side = SOUTH;
		}
		//Check if ray has hit a wall
		if (data->map[data->mapY][data->mapX] != '0' && data->map[data->mapY][data->mapX] != '2')
			hit = 1;
	}
}

void calculate_step(t_data *data)
{
	if (data->rayDirX < 0)
	{
		data->stepX = -1;
		data->dx = (data->pos_x - data->mapX) * data->delta_x;
	}
	else
	{
		data->stepX = 1;
		data->dx = (data->mapX + 1.0 - data->pos_x) * data->delta_x;
	}
	if (data->rayDirY < 0)
	{
		data->stepY = -1;
		data->dy = (data->pos_y - data->mapY) * data->delta_y;
	}
	else
	{
		data->stepY = 1;
		data->dy = (data->mapY + 1.0 - data->pos_y) * data->delta_y;
	}
}




void draw(t_data *data, int x)
{
	(void)x;
	int lineHeight;
	//if (data->perpWallDist != 0)
		lineHeight = (int)(data->height / data->perpWallDist);
	//else
	//	lineHeight = (int)data->height;

	//calculate lowest and highest pixel to fill in current stripe
	int drawStart = (-lineHeight / 2) + (data->height / 2);
	if (drawStart < 0)
		drawStart = 0;

	int drawEnd = (lineHeight / 2) + (data->height / 2);
	if (drawEnd >= data->height)
		drawEnd = data->height - 1;

	double wallx = 0;
	if (data->side == WEST || data->side == EAST)
		wallx = data->pos_y + (data->perpWallDist * data->rayDirY);
	else
		wallx = data->pos_x + (data->perpWallDist * data->rayDirX);

	wallx -= floor(wallx);
	//printf("WALLX %f \n", wallx);

	int texX = (int)(wallx * (double)data->t->w);
	//printf("TEXX 1 %d \n", texX);

	if ((data->side == EAST || (data->side == WEST)) && data->rayDirX > 0)
		texX = data->t->w - texX - 1;
	if ((data->side == NORTH || data->side == SOUTH) && data->rayDirY < 0)
		texX = data->t->w - texX - 1;
	//printf("TEXX 2 %d \n", texX);

	double step = (1.0 * data->t->h) / lineHeight;
	// Starting texture coordinate
	double texPos = (drawStart - (data->height / 2) + (lineHeight / 2)) * step;

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

	//printf ("side : %c \n", data->t->side);

//	int fog = 0x38eeff;

	for (int y = drawStart; y < drawEnd; y++)
	{
		int texY = (int)texPos & (data->t->h - 1);
		texPos += step;
		data->color = ((unsigned int *)data->t->imgaddr)[data->t->h * texY + texX];
	//	data->color = (1 - 0.75) * (data->color >> 4) + 0.75 * RED;
	//	data->color = ((1 - (data->zbuffer[x] * 0.75 ))  * data->color) + ((data->zbuffer[x] * 0.75 * BLUE)); // FOG TRY
		//printf ("%f", (data->zbuffer[x] * 0.75));
		my_mlx_pixel_put(data, x, y, data->color);
	}
	//printf ("ppd %f \n", data->perpWallDist);

}

void dda(t_data *data)
{
	int x;
	x = -1;
	while (x++ < data->width)
	{
		data->cameraX = 2 * x / (double)data->width - 1; //x-coordinate in camera space
		data->rayDirX = data->dirX + (data->planeX * data->cameraX);
		data->rayDirY = data->dirY + (data->planeY * data->cameraX);
		data->mapX = (int)data->pos_x;
		data->mapY = (int)data->pos_y;
		data->delta_x = (data->rayDirY == 0) ? 0 : ((data->rayDirX == 0) ? 1 : fabs(1 / data->rayDirX));
		data->delta_y = (data->rayDirY == 0) ? 0 : ((data->rayDirY == 0) ? 1 : fabs(1 / data->rayDirY));
		calculate_step(data);
		perform_dda(data);
		if (data->side == WEST || data->side == EAST)
			data->perpWallDist = (data->mapX - data->pos_x + (1 - data->stepX) / 2) / data->rayDirX;
		else
			data->perpWallDist = (data->mapY - data->pos_y + (1 - data->stepY) / 2) / data->rayDirY;
		draw(data, x);
		data->zbuffer[x] = data->perpWallDist;
	}
	if (data->spr != NULL)
	{
		sprite_casting(data);
		sprite_drawing(data, x);
	}

}

void init_base(t_data *data)
{
	data->error = 0;
	data->pos_x = -1;
	data->pos_y = -1;
	data->info->ceiling_rgb = -1;
	data->info->floor_rgb = -1;
}

int main()
{
	t_data data;
	t_display info;
	int fd;
	char *file;

	file = NULL;
	fd = open("map1.cub", O_RDONLY);
	if (!fd)
		printf("Bad argument.\n");
	data.info = &info;
	init_base(&data);
	ft_parse(fd, &data);
	if (data.error != 0)
		return (-1);
	if (init_struct(&data) == -1)
		return (-1);
	display(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_hook(data.win, 2, 1L << 0, key_hook, &data);
	mlx_hook(data.win, 17, (1L << 17), red_cross, &data);
	mlx_loop(data.mlx);
	
}
