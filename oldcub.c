#include "cub3d.h"

int		red_cross(void)
{
	exit(0);
	return (0);
}
 void display(t_data *data)
 {
	 draw_tab(data);
	 mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
 }

int		mouse_hook(int button, int x, int y, t_data *data)
{
	// int width;
	// int height;

    (void)data;
	if (button == 1){
	printf( "X %d AND Y %d IS PRESSED !\n", x, y);
	}
	return (0);
}

 void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    //int *pixels;
	char *dst;

	//pixels = (int *)data->imgaddr;

   dst = data->imgaddr + (y * data->line_length + x * (data->bits_per_pixel / 8));
 //  printf ("PIXEL %u\n", (unsigned int)dst);
  	if (x >= 0 && x < data->width && y >= 0 && y < data->height)
   		*(unsigned int*)dst = color;
   // pixels[(y * data->width + x)] = color;
}


void     fill_square(int width, int height, t_data *data)
{
    int i = 0;
    int j = 0;

  while (i < height)
       {
           while (j < width)
           {
                my_mlx_pixel_put(data, j, i, 0xff0000);
                j++;
           }
           j = 0;
           i++;
       }
}

int     set_map(int x, int y, int width, int height, t_data *data)
{
    int xbis = x;
    int ybis = y;

        while (y < ybis + height)
       {
           while (x < xbis + width)
           {
			   if (ybis%2 == 0)
                	my_mlx_pixel_put(data, x, y,  0xffd700);
				else
					my_mlx_pixel_put(data, x, y,  0xd433ff);
				x++;
           }
           x = xbis;
           y++;
       }
       return 0;
}


int     set_player(int x, int y, int width, int height, t_data *data)
{
    int xbis = x;
    int ybis = y;

        while (y < ybis + height)
       {
           while (x < xbis + width)
           {
                my_mlx_pixel_put(data, x, y,  0x4b0082);
                x++;
           }
           x = xbis;
           y++;
       }
       return 0;
}



 int   key_hook(int keycode, t_data *data)
 {
        if (keycode == KEY_UP)
		{
            data->pos_y -= 10;
		}
        if (keycode == KEY_DOWN)
             data->pos_y += 10;
        if (keycode == KEY_LEFT)
		{
            data->pos_x -= 10;
			data->angle -= 0.1;
		}
         if (keycode == KEY_RIGHT)
            data->pos_x += 10;
		printf("POS X= %f POS Y= %f\n",data->pos_x, data->pos_y );
		printf ("IF WAS ON MAP %d ___ %d \n", (int)data->pos_x/64, (int)data->pos_y/64 );


	int i = 0;
	int j = 0;
    for (i = 0; i < data->map_h; i++) {
        for (j = 0; j < data->map_w; j++) {
			printf ("map[%d][%d] ", i, j);
            printf("%c ", data->map[i][j]);
        }
        printf("\n");
    }

	//printf ("TEST : %c \n", data->map[5][3]);

		if (data->map[(int)data->pos_y/64][(int)data->pos_x/64] != '0')
		{
			printf ("%c\n",data->map[(int)data->pos_y/64][(int)data->pos_x/64] );
			printf ("HIT WALL AT %f ___ %f \n", data->pos_y/64, data->pos_x/64 );
		}
        fill_square(data->width, data->height, data);
		set_player(data->pos_x , data->pos_y, 10,10, data);
		display(data);
    return (1);

 }




void    draw_tab(t_data *data)
{
    int i = 0;
    int j = 0;
    int x = 0;
    int y = 0;

	// j = x, les colonnes
	// i = y, les lignes \n
        while (i < data->map_h)
        {
            while (j < data->map_w)
            {
                if (data->map[i][j] > '0' && data->map[i][j] != 'N')
                    set_map(x, y,64, 64, data);
                j++;
                x += data->map_s;
            }
            j = 0;
            x = 0;
            i++;
            y += data->map_s;
        }
}


void 	init_struct(t_data *data)
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



}


int main()
{
    t_data data;
	int		fd;
	char	*file;

	file = NULL;
	// if (ac != 2)
	// {
	// 	printf("No map given.\n");
	// 	return (-1);
	// }
	init_struct(&data);
	fd = open("map1.cub", O_RDONLY);
	if (!fd)
		printf("Bad argument.\n");
	ft_parse(fd, &data);
	printf ("%f --- %f \n", data.pos_x, data.pos_y );


	data.pos_x = data.pos_x * data.width/data.map_w;
	data.pos_y = data.pos_y  * data.height/data.map_h;

	// int i = 0;
	// int j = 0;
	//  for (i = 0; i < data.map_h; i++) {
    //     for (j = 0; j < data.map_w; j++) {
	// 		printf ("map[%d][%d] ", i, j);
    //         printf("%c ", data.map[i][j]);
    //     }
    //     printf("\n");
    // }

	int x = 0;

	while (x++ < data.width)
	{
	 data.cameraX = 2 * x / (double)data.width - 1; //x-coordinate in camera space
     data.rayDirX = data.dirX + data.planeX * data.cameraX;
     data.rayDirY = data.dirY + data.planeY * data.cameraX;
	 printf ("RAYDIR X - Y = %f - %f ",data.rayDirX, data.rayDirY);
	}
	set_player(data.pos_x , data.pos_y, 64, 64, &data);


  //1events
  //2 draw according to events
  //3 render



	 //   mlx_hook(data.win, 17, (1L << 17), red_cross, &data); //fonctionne

        //mlx_hook(data.win, 2, 1L<<0, set_player, &data);

		//draw_tab(tab, &data);
        printf (" %f ___ %f  ",data.pos_x, data.pos_y);
       // mlx_clear_window(data.mlx, data.win);
	  	//set_player(data.pos_x, data.pos_y, 10, 10, &data);
		draw_tab(&data);
        mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
		mlx_hook(data.win, 2, 1L<<0, key_hook, &data);
		mlx_hook(data.win, 17, (1L << 17), red_cross, &data);

        mlx_loop(data.mlx);


    return (0);
}

