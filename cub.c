#include "cub3d.h"

void display(t_data *data)
{
	// printf ("**DISPLAY**\n");
	fill_black(data);
	fill_ceiling(data);
	fill_floor(data);

	dda(data);

	if (data->displaymap == 1)
	{
		//printf ("**DISPLAy 1 OK**\n");
		set_map(data);
		//printf ("**MAP OK**\n");
		set_player(data);
		//	printf ("**PLAYRE OK**\n");
		data->color = 0xffffff;
		bresenham(data->pos_x * data->minimap_size + data->width / 4, data->pos_y * data->minimap_size + data->height * 0.7, (data->pos_x + data->dirX) * data->minimap_size + data->width / 4, (data->pos_y + data->dirY) * data->minimap_size + data->height * 0.7, data);
	}
	// data->color = 0xADD8E6;
	char *positionX = ft_ftoa(data->pos_x, 4);
	char *stringX = ft_strjoin("X = ", positionX);

	char *positionY = ft_ftoa(data->pos_y, 4);
	char *stringY = ft_strjoin("Y = ", positionY);

	mlx_new_image(data->mlx, data->width, data->height);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_string_put(data->mlx, data->win, 30, data->height - 50, BLUE, stringX);
	mlx_string_put(data->mlx, data->win, 30, data->height - 25, BLUE, stringY);
	mlx_string_put(data->mlx, data->win, 0, 0, WHITE, "COUCOU");
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->imgaddr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	if (x >= 0 && x < data->width && y >= 0 && y < data->height)
		*(unsigned int *)dst = color;
}


int checkzero_letter(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return 1;
	return 0;
}

int key_hook(int keycode, t_data *data)
{
	if (keycode == KEY_UP)
	{
		if (checkzero_letter(data->map[(int)(data->pos_y)][(int)(data->pos_x + data->dirX * 0.10)]))
			data->pos_x += data->dirX * 0.10;

		if (checkzero_letter(data->map[(int)(data->pos_y + data->dirY * 0.10)][(int)(data->pos_x)]))
			data->pos_y += data->dirY * 0.10;
	}
	if (keycode == KEY_DOWN)
	{
		if (checkzero_letter(data->map[(int)(data->pos_y)][(int)(data->pos_x - data->dirX * 0.10)]))
			data->pos_x -= data->dirX * 0.10;
		if (checkzero_letter(data->map[(int)(data->pos_y - data->dirY * 0.10)][(int)(data->pos_x)]))
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

void init_struct(t_data *data)
{
	data->mlx = mlx_init();

	data->win = mlx_new_window(data->mlx, data->width, data->height, "who run the world ?");
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	data->imgaddr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	data->map_s = 64; //bloc de 64 px

	data->planeX = 0;
// titillier ca pour les pos de depart??? pk??????

	data->planeY = -0.66;

	data->minimap_size = data->width / 30;
	data->displaymap = 1;
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
			data->side = 0;
		}
		else
		{
			data->dy += data->delta_y;
			data->mapY += data->stepY;
			data->side = 1;
		}
		//Check if ray has hit a wall
		if (data->map[data->mapY][data->mapX] != '0')
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
	if (data->perpWallDist != 0)
		lineHeight = (int)(data->height / data->perpWallDist);
	else
		lineHeight = (int)data->height;

	//calculate lowest and highest pixel to fill in current stripe
	int drawStart = (-lineHeight / 2) + (data->height / 2);
	if (drawStart < 0)
		drawStart = 0;

	int drawEnd = (lineHeight / 2) + (data->height / 2);
	if (drawEnd >= data->height)
		drawEnd = data->height - 1;

	// if (data->side == 1)
	// 	data->color = RED;
	// else
	// 	data->color = YELLOW;

	//bresenham(x, drawStart, y, drawEnd, data);
	double wallx = 0;

	if (data->side == 0)
		wallx = data->pos_y + (data->perpWallDist * data->rayDirY);
	else
		wallx = data->pos_x + (data->perpWallDist * data->rayDirX);

	wallx -= floor(wallx);
	//printf("WALLX %f \n", wallx);


	int texX = (int)(wallx * (double)data->t->w);
	//printf("TEXX 1 %d \n", texX);


	if(data->side == 0 && data->rayDirX > 0)
		texX = data->t->w - texX - 1;
	if(data->side == 1 && data->rayDirY < 0)
		texX = data->t->w - texX - 1;
	//printf("TEXX 2 %d \n", texX);

	double step = (1.0 * data->t->h) / lineHeight;
	// Starting texture coordinate
	double texPos = (drawStart - (data->height / 2) + (lineHeight / 2)) * step;


	if (data->side == 1)
		while (data->t->side != 's')
  			data->t = data->t->next;
	else
		while (data->t->side != 'n')
  			data->t = data->t->next;


	//printf ("side : %c \n", data->t->side);

	for (int y = drawStart; y < drawEnd; y++)
	{
		int texY = (int)texPos & (data->t->h - 1);
		texPos += step;
		data->color = ((unsigned int *)data->t->imgaddr)[data->t->h * texY + texX];
		my_mlx_pixel_put(data, x, y, data->color);
	}
}

void dda(t_data *data)
{
	int x = 0;

	printf ("data dirx =  %f\n", data->dirX);
	printf ("data diry =  %f\n", data->dirY);

	while (x++ < data->width)
	{
		data->cameraX = 2 * x / (double)data->width - 1; //x-coordinate in camera space
		data->rayDirX = data->dirX + data->planeX * data->cameraX;
		data->rayDirY = data->dirY + data->planeY * data->cameraX;
		//printf("RAYDIR X - Y = %f - %f \n", data->rayDirX, data->rayDirY);

		data->mapX = (int)data->pos_x;
		//printf ("POS %f MAP %d\n", data->pos_x, data->mapX);
		data->mapY = (int)data->pos_y;
		//length of ray from one x or y-side to next x or y-side



	    // Alternative code for deltaDist in case division through zero is not supported
    //  double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : abs(1 / rayDirX));
     // double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : abs(1 / rayDirY));

		// if (data->rayDirY == 0 && data->rayDirX != 0)
		// 	data->delta_x = 0;
		// else if (data->rayDirX == 0)
		// 	data->delta_x = 1;
		// else 
		printf ("raydir x %f \n", data->rayDirX);
		printf ("raydir y %f \n", data->rayDirY);

		if (data->rayDirY != 0 && data->rayDirY != 0)
			data->delta_x = fabs(1 / data->rayDirX);
		else
			data->delta_x = 0.66;



		// if (data->rayDirX == 0)
		// 	data->delta_y = 0;
		// else if (data->rayDirY == 0)
		// 	data->delta_y = 1;
		// else
			data->delta_y = fabs(1 / data->rayDirY);

		calculate_step(data);
		perform_dda(data);


		if (data->side == 0)
			data->perpWallDist = (data->mapX - data->pos_x + (1 - data->stepX) / 2) / data->rayDirX;
		else
			data->perpWallDist = (data->mapY - data->pos_y + (1 - data->stepY) / 2) / data->rayDirY;
		draw(data, x);
	}
}

void loadimage(t_data *data)
{
	t_text *t;
	t_text *head;


	t = (t_text *)malloc(sizeof(t_text));
	head = t;

	t->side = 'n';

	t->img = mlx_xpm_file_to_image(data->mlx, data->info->north_text, &t->w, &t->h);
	t->imgaddr = mlx_get_data_addr(t->img, &t->bits_per_pixel, &t->line_length, &t->endian);
	t->next = (t_text *)malloc(sizeof(t_text));

	t = t->next;
	t->side = 's';

	t->img = mlx_xpm_file_to_image(data->mlx, data->info->south_text, &t->w, &t->h);
	t->imgaddr = mlx_get_data_addr(t->img, &t->bits_per_pixel, &t->line_length, &t->endian);
	t->next = (t_text *)malloc(sizeof(t_text));

	t = t->next;
	t->side = 'w';

	t->img = mlx_xpm_file_to_image(data->mlx, data->info->west_text, &t->w, &t->h);
	t->imgaddr = mlx_get_data_addr(t->img, &t->bits_per_pixel, &t->line_length, &t->endian);
	t->next = (t_text *)malloc(sizeof(t_text));

	t = t->next;

	t->img = mlx_xpm_file_to_image(data->mlx, data->info->east_text, &t->w, &t->h);
	t->imgaddr = mlx_get_data_addr(t->img, &t->bits_per_pixel, &t->line_length, &t->endian);
	t->next = head;

	data->t = head;
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
	data.error = 0;
	data.pos_x = -1;
	data.pos_y = -1;
	ft_parse(fd, &data);
	if (data.error != 0)
		return (error_message(data.error));
	printf("coucou\n");
	init_struct(&data);
	loadimage(&data);

	display(&data);

	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_hook(data.win, 2, 1L << 0, key_hook, &data);
	mlx_hook(data.win, 17, (1L << 17), red_cross, &data);

	mlx_loop(data.mlx);
}
