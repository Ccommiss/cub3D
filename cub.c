#include "cub3d.h"




 void display(t_data *data)
 {
	 //mlx_clear_window(data->mlx, data->win);
	fill_black(data);
	fill_ceiling(data);
	fill_floor(data);
	dda(data);

	if (data->displaymap == 1)
	{
		set_map(data);
		set_player(data);
		bresenham(data->pos_x * data->minimap_size + data->width/2, data->pos_y * data->minimap_size + data->height - 200 , (data->pos_x + data->dirX) * data->minimap_size + data->width/2 , (data->pos_y + data->dirY ) * data->minimap_size + data->height - 200 , data);

	}
	// data->color = 0xADD8E6;
	char *positionX = ft_ftoa(data->pos_x, 4);
	char *stringX = ft_strjoin("X = ", positionX);
	
	char *positionY = ft_ftoa(data->pos_y, 4);
	char *stringY = ft_strjoin("Y = ", positionY);
	
	printf ("%s - %s\n", positionX, positionY);
	


	//data->color = 0xFFFFFF;
//	bresenham(data->pos_x * 64, data->pos_y * 64, (data->pos_x + data->dirX + (data->cameraX - 1)) * 64, (data->pos_y + data->dirY + (data->cameraY + 1)) * 64, data);
//	bresenham(data->pos_x * 64, data->pos_y * 64, (data->pos_x + data->dirX + data->cameraX) * 64, (data->pos_y + data->dirY + data->cameraY) * 64, data);

//	bresenham(data->pos_x * 64, data->pos_y * 64, (data->rayDirX) * 64, (data->rayDirY) * 64, data);
//	bresenham(data->pos_x * 64, data->pos_y * 64, (data->pos_x + data->dirX + data->planeX * 0) * 64, (data->pos_y + data->dirY + data->planeY* 600) * 64, data);
//	bresenham(data->pos_x * 64, data->pos_y * 64, (data->pos_x + data->dirX + data->planeX * 600) * 64, (data->pos_y + data->dirY + data->planeY * 600) * 64, data);





	mlx_new_image(data->mlx,data->width, data->height);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_string_put(data->mlx, data->win, 30, data->height - 50, BLUE, stringX);
	mlx_string_put(data->mlx, data->win, 30, data->height - 25, BLUE, stringY);
	mlx_string_put(data->mlx, data->win, 0, 0, WHITE, "COUCOU");
 }

 void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

   dst = data->imgaddr + (y * data->line_length + x * (data->bits_per_pixel / 8));
  	if (x >= 0 && x < data->width && y >= 0 && y < data->height)
   		*(unsigned int*)dst = color;
}

void 	bresenham(int xdep, int ydep, int xfin, int yfin, t_data *data)
{
   float a=0;
   int temp=0;
   int cste=0;

   unsigned int dy;
   unsigned int dx;

   dx=abs(xfin-xdep);
   dy=abs(yfin-ydep);
if(dx>=dy && dx!=0 && dy!=0)
{
   if(xdep>xfin)
   {
      temp=xdep;
      xdep=xfin;
      xfin=temp;

      temp=ydep;
      ydep=yfin;
      yfin=temp;
   }
   a=((float)(yfin-ydep)/(xfin-xdep));

   for(unsigned int x=0;x<dx+1;x++)
   {
      my_mlx_pixel_put(data,x+xdep,ydep+(x*a)+cste, data->color);
   }
}

if(dx<dy && dx!=0 && dy!=0)
{
		   printf ("ALOHA 2\n");
   if(ydep>yfin)
   {
   temp=ydep;
   ydep=yfin;
   yfin=temp;

   temp=xdep;
   xdep=xfin;
   xfin=temp;
   }
   a=((float)(xfin-xdep)/(yfin-ydep));

   for(unsigned int y=0;y<dy+1;y++)
   {
	my_mlx_pixel_put(data,xdep+(y*a)+cste,y+ydep, data->color);
   }
}

if(dx==0)
{
   if(ydep>yfin)
   {
      temp=ydep;
      ydep=yfin;
      yfin=temp;
   }
   for(int y=ydep;y<yfin+1;y++)
   	my_mlx_pixel_put(data,xdep,y, data->color);
}
if(dy==0)
{
      if(xdep>xfin)
   {
      temp=xdep;
      xdep=xfin;
      xfin=temp;
   }
   for(int x=xdep;x<xfin+1;x++)
   my_mlx_pixel_put(data,x,ydep,data->color);
}
}

int key_hook(int keycode, t_data *data)
{
	if (keycode == KEY_UP)
	{
		if (data->map[(int)(data->pos_y)][(int)(data->pos_x + data->dirX * 0.10)] == '0')
			data->pos_x += data->dirX * 0.10;
		if (data->map[(int)(data->pos_y - data->dirY * 0.10)][(int)(data->pos_x)] == '0')
			data->pos_y += data->dirY * 0.10;
	}
	if (keycode == KEY_DOWN)
	{
		if (data->map[(int)(data->pos_y)][(int)(data->pos_x - data->dirX * 0.10)] == '0')
			data->pos_x -= data->dirX * 0.10;
		if (data->map[(int)(data->pos_y - data->dirY * 0.10)][(int)(data->pos_x)] == '0')
			data->pos_y -= data->dirY * 0.10;
	}
	if (keycode == KEY_LEFT) //ROTATION A FAIRE
	{
      //both camera direction and camera plane must be rotated
      double oldDirX = data->dirX;
      data->dirX = data->dirX * cos(0.2) - data->dirY * sin(0.2);
	  data->dirY = oldDirX * sin(0.2) + data->dirY * cos(0.2);

	  double oldPlaneX = data->planeX;
	  data->planeX = data->planeX * cos(0.2) - data->planeY * sin(0.2);
	  data->planeY = oldPlaneX * sin(0.2) + data->planeY * cos(0.2);
    }
	if (keycode == KEY_RIGHT)
	{
	  double oldDirX = data->dirX;
      data->dirX = data->dirX * cos(-0.02) - data->dirY * sin(-0.02);
      data->dirY = oldDirX * sin(-0.02) + data->dirY * cos(-0.02);
      double oldPlaneX = data->planeX;
      data->planeX = data->planeX * cos(-0.02) - data->planeY * sin(-0.02);
      data->planeY = oldPlaneX * sin(-0.02) + data->planeY * cos(-0.02);
	}
	if (keycode == KEY_SPACE)
	{
		if (data->displaymap == 0)
			data->displaymap = 1;
		else
			data->displaymap = 0;
	}
		


	display(data);
	return 1;
}

void init_struct(t_data *data)
{
	data->mlx = mlx_init();
	data->width = 1080;
	data->height = 600;
	data->win = mlx_new_window(data->mlx, data->width, data->height, "who run the world ?");
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	data->imgaddr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	data->map_s = 64; //bloc de 64 px
	data->angle = 0;

	data->dirX = -1;
	data->dirY = 0;
	data->planeX = 0;
	data->planeY = 0.66;

	data->minimap_size = 30;
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
		if (data->map[data->mapY][data->mapX] > '0')
		{
			hit = 1;
		}
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



void draw (t_data *data, int x)
{
	int lineHeight;
	if (data->perpWallDist != 0)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
		lineHeight = (int)(data->height / data->perpWallDist);
	else 
		lineHeight = (int)data->height;

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + data->height/ 2;
      if(drawStart < 0)
	  	drawStart = 0;

      int drawEnd = lineHeight / 2 + data->height/ 2;
      if(drawEnd >= data->height)
	  	drawEnd = data->height - 1;
		
	if (data->side == 1)
		data->color = RED;
	else 
		data->color = YELLOW;
	bresenham(x, drawEnd, x, drawStart, data);
}

void dda(t_data *data)
{
	int x = 0;

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

		calculate_step(data);
		perform_dda(data);
		if (data->side == 0)
			data->perpWallDist = (data->mapX - data->pos_x + (1 - data->stepX) / 2) / data->rayDirX;
      	else
		  	data->perpWallDist = (data->mapY - data->pos_y + (1 - data->stepY) / 2) / data->rayDirY;
		draw(data, x);
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

	int i;		
 	int j;
	printf ("DATA.maph = %d \n", data.map_h);
	printf ("DATA.mapZ = %d \n", data.map_w);

 	for (i = 0; i < data.map_h; i++)		
 	{		
 		for (j = 0; j < data.map_w; j++)		
 		{		
 			printf("[%d][%d]", i, j);		
 			printf("%c ", data.map[i][j]);		
 		}		
 		printf("\n");		
 	}		

	display(&data);
	//dda(&data);
//	set_player(&data);
	//set_map(&data);
	
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_hook(data.win, 2, 1L<<0, key_hook, &data);
	//	mlx_hook(data.win, 17, (1L << 17), red_cross, &data);

	mlx_loop(data.mlx);
}

















  