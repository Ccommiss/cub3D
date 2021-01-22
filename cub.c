#include "cub3d.h"

 void display(t_data *data)
 {
	 mlx_clear_window(data->mlx, data->win);
	 set_player(data);
	 set_map(data);
	 mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
 }

 void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

   dst = data->imgaddr + (y * data->line_length + x * (data->bits_per_pixel / 8));
  	if (x >= 0 && x < data->width && y >= 0 && y < data->height)
   		*(unsigned int*)dst = color;
}



int key_hook(int keycode, t_data *data)
{
	if (keycode == KEY_UP)
	{	
		printf("KEUP PRESSED\n");
		if (data->map[(int)(data->pos_x + data->dirX * 0.2)][(int)(data->pos_y)] == '0')
			data->pos_x += data->dirX * 0.2;
		if (data->map[(int)(data->pos_x)][(int)(data->pos_y - data->dirY * 0.2)] == '0')
			data->pos_y += data->dirY * 0.2;
	}
	if (keycode == KEY_DOWN)
	{
		if (data->map[(int)(data->pos_x - data->dirX * 0.2)][(int)(data->pos_y)] == '0')
			data->pos_x -= data->dirX * 0.2;
		if (data->map[(int)(data->pos_x)][(int)(data->pos_y - data->dirY * 0.2)] == '0')
			data->pos_y -= data->dirY * 0.2;
	}
	// if (keycode == KEY_LEFT) ROTATION A FAIRE

	// if (keycode == KEY_RIGHT)

	display(data);
	return 1;
}

void init_struct(t_data *data)
{
	data->mlx = mlx_init();
	data->width = 600;
	data->height = 500;
	data->win = mlx_new_window(data->mlx, data->width, data->height, "who run the world ?");
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	data->imgaddr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	data->map_s = 64; //bloc de 64 px
	data->angle = 0;

	data->dirX = -1;
	data->dirY = 0;
	data->planeX = 0;
	data->planeY = 0.66;
	data->pos_x = 22;
	data->pos_y = 12;
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
		//printf("\n");
		if (data->map[data->mapY][data->mapX] > '0')
		{
		//	printf("HIT X %d Y %d = ", data->mapX, data->mapY);
			hit = 1;
		}
	}
}


void calculate_step(t_data *data)
{
	//printf ("CALCULATING STEPS : \n");
	if (data->rayDirX < 0)
	{
		data->stepX = -1;
		data->dx = (data->pos_x - data->mapX) * data->dx;
	}
	else
	{
		data->stepX = 1;
		data->dx = (data->mapX + 1.0 - data->pos_x) * data->dx;
	}
	if (data->rayDirY < 0)
	{
		data->stepY = -1;
		data->dy = (data->pos_y - data->mapY) * data->dy;
	}
	else
	{
		data->stepY = 1;
		data->dy = (data->mapY + 1.0 - data->pos_y) * data->dy;
	}
}



void draw (t_data *data)
{
	  int lineHeight = (int)(data->height / data->perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + data->height/ 2;
      if(drawStart < 0)drawStart = 0;
      int drawEnd = lineHeight / 2 + data->height/ 2;
      if(drawEnd >= data->height)drawEnd = data->height - 1;
}

void dda(t_data *data)
{
	int x = 0;
	printf("DDA :\n\n");

	int i;
	int j;
	for (i = 0; i < data->map_h; i++)
	{
		for (j = 0; j < data->map_w; j++)
		{
			printf("yo map[%d][%d] ", i, j);
			printf("%c ", data->map[i][j]);
		}
		printf("\n");
	}

	printf("%d \n", data->width);
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
		data->delta_x = fabs(1 / data->rayDirX);
		data->delta_y = fabs(1 / data->rayDirY);


		//calculate step and initial sideDist
		calculate_step(data);
		perform_dda(data);
		if (data->side == 0)
			data->perpWallDist = (data->mapX - data->pos_x + (1 - data->stepX) / 2) / data->rayDirX;
      	else
		  data->perpWallDist = (data->mapY - data->pos_y + (1 - data->stepY) / 2) / data->rayDirY;
		draw(data);

		//perform DDA

		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		// if (data->side == 0)
		// 	perpWallDist = (mapX - data->pos_x + (1 - stepX) / 2) / data->rayDirX;
		// else
		// 	perpWallDist = (mapY - data->pos_y + (1 - stepY) / 2) / data->rayDirY;
	}
}

int main()
{
	t_data data;
	int fd;
	char *file;

	file = NULL;
	init_struct(&data);
	fd = open("map1.cub", O_RDONLY);
	if (!fd)
		printf("Bad argument.\n");
	ft_parse(fd, &data);
	set_player(&data);
	set_map(&data);
	printf("%f --- %f \n", data.pos_x, data.pos_y);
	dda(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_hook(data.win, 2, 1L<<0, key_hook, &data);
	//	mlx_hook(data.win, 17, (1L << 17), red_cross, &data);

	mlx_loop(data.mlx);
}
