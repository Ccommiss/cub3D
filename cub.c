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
		set_compass(data);
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
	if (c == '0') // || c == '2') //et 2 sil faut traverser
		return (1);
	return 0;
}

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

t_spr *sort_sprites(t_data *data, t_spr *head)
{
	t_spr *tmp;
	t_spr *tmp_next;
	int tmpx;
	int tmpy;
	int tmpdist;

	tmp = data->spr;
	tmp_next = data->spr->next;
	while (tmp_next != NULL)
	{
		while (tmp_next != tmp)
		{
			if (tmp_next->distance > tmp->distance)
			{
				tmpx = tmp->x;
				tmpy = tmp->y;
				tmpdist = tmp->distance;
				tmp->x = tmp_next->x;
				tmp->y = tmp_next->y;
				tmp->distance = tmp_next->distance;
				tmp_next->x = tmpx;
				tmp_next->y = tmpy;
				tmp_next->distance = tmpdist;
			}
			tmp = tmp->next;
		}
		tmp = head;
		tmp_next = tmp_next->next;
	}
	return (tmp); // Place holder
}

void sprite_casting(t_data *data)
{
	//printf("INDEX IN SPR CASTING = %d \n", data->spr->index);
	t_spr *head;
	head = data->spr->head; //on make sure on est bien au debut

	while (data->spr != NULL)
	{
		data->spr->distance = (pow((data->pos_x - data->spr->x), 2) + pow((data->pos_y - data->spr->y), 2));
		//printf(" INDEX = %d, distance = %f \n", data->spr->index, data->spr->distance);
		data->spr = data->spr->next;
	}
	data->spr = head;
	data->spr = sort_sprites(data, head);
	data->spr = head;
}

void sprite_drawing(t_data *data, int x)
{
	t_spr *head = data->spr->head;
	//	for(int i = 0; i < numSprites; i++)
	while (data->spr != NULL)
	{
		//translate sprite position to relative to camera
		double spriteX = (data->spr->x + 0.5) - data->pos_x; // + 0.5 = ajout de moi car semblait pas bon mais rustine


		double spriteY = (data->spr->y + 0.5) - data->pos_y;
	//	printf ("SPRpos X = %f \n SPRpos Y = %f \n",data->spr->x, data->spr->y );

	//	printf ("SPRITE X = %f \n SPRITE Y = %f \n",spriteX, spriteY );

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (data->planeX * data->dirY - data->dirX * data->planeY); //required for correct matrix multiplication
		if (invDet == 0)
			printf ("INV DET VAUT 0 \n\n");

		double transformX = invDet * (data->dirY * spriteX - data->dirX * spriteY);
		double transformY = invDet * ((-data->planeY * spriteX) + (data->planeX * spriteY)); //this is actually the depth inside the screen, that what Z is in 3D
		// je pense que le pb vient de la, ou vrmt sprite x mais pk ??


		int spriteScreenX = (int)((data->width / 2) * (1 + transformX / transformY));

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(data->height / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + data->height / 2;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + data->height / 2;
		if (drawEndY >= data->height)
			drawEndY = data->height - 1;

		//calculate width of the sprite
		int spriteWidth = abs((int)(data->height / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;

		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= data->width)
			drawEndX = data->width - 1;

		//printf( "START %d - END %d \n\n", drawStartX, drawEndX);
		//printf( "trnas Y %f \n\n", transformY);




		//loop through every vertical stripe of the sprite on screen
		for (int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * data->spw / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance

			unsigned int color;

			//printf ("buffer %f \n ", data->zbuffer[stripe]);

			if (transformY > 0 && stripe > 0 && stripe < data->width && transformY <= data->zbuffer[stripe]) //en enlevant derniere condition ca affiche tout
			{
				for (int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					int d = (y)*256 - data->height * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * data->sph) / spriteHeight) / 256;
					color = ((unsigned int *)data->sprimgaddr)[data->spw * texY + texX];
					//color = (1 - 0.25) * color + 0.25 * 0x000001; // FOG TRY

					if ((color & 0x00FFFFFF) != 0)
						my_mlx_pixel_put(data, stripe, y, color);
					(void)x;
				}
			}
		}
		data->spr = data->spr->next;
	}
	data->spr = head;
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
	int x = -1;

	printf("data dirx =  %f\n", data->dirX);
	printf("data diry =  %f\n", data->dirY);
	printf("PLANE X = %f\n", data->planeX);
	printf("PLANE Y = %f\n", data->planeY);

	while (x++ < data->width)
	{
		data->cameraX = 2 * x / (double)data->width - 1; //x-coordinate in camera space
		if (x == 0)
			printf("CAMERA X = %f\n", data->cameraX);
		data->rayDirX = data->dirX + (data->planeX * data->cameraX);

		data->rayDirY = data->dirY + (data->planeY * data->cameraX);

		if (x == 0)
			printf("RAYDIR X - Y = %f - %f \n", data->rayDirX, data->rayDirY);

		data->mapX = (int)data->pos_x;
		//printf ("POS %f MAP %d\n", data->pos_x, data->mapX);
		data->mapY = (int)data->pos_y;
		//length of ray from one x or y-side to next x or y-side

		// Alternative code for deltaDist in case division through zero is not supported
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
	sprite_casting(data);
	sprite_drawing(data, x);

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
	printf("coucou\n");
	if (init_struct(&data) == -1)
		return (-1);
	display(&data);

	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_hook(data.win, 2, 1L << 0, key_hook, &data);
	mlx_hook(data.win, 17, (1L << 17), red_cross, &data);
	mlx_loop(data.mlx);
}
