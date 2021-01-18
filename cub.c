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
            data->pos_y -= 10;
        if (keycode == KEY_DOWN)
             data->pos_y += 10;
        if (keycode == KEY_LEFT)
            data->pos_x -= 10;
         if (keycode == KEY_RIGHT)
            data->pos_x += 10;
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
                    set_map(x, y, data->width/data->map_w, data->height/data->map_h, data);
                j++;
                x += data->width/data->map_w;
            }
            j = 0;
            x = 0;
            i++;
            y += data->height/data->map_h;
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
printf ("%d --- %d \n", data.pos_x, data.pos_y );
	data.pos_x = data.pos_x * data.width/data.map_w;
	data.pos_y =  data.pos_y  * data.height/data.map_h;

	set_player(data.pos_x , data.pos_y, data.width/6, data.height/5, &data);


  //1events
  //2 draw according to events
  //3 render



	 //   mlx_hook(data.win, 17, (1L << 17), red_cross, &data); //fonctionne

        //mlx_hook(data.win, 2, 1L<<0, set_player, &data);

		//draw_tab(tab, &data);
        printf (" %d ___ %d  ",data.pos_x, data.pos_y);
       // mlx_clear_window(data.mlx, data.win);
	  	//set_player(data.pos_x, data.pos_y, 10, 10, &data);
		draw_tab(&data);
        mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
		mlx_hook(data.win, 2, 1L<<0, key_hook, &data);
		mlx_hook(data.win, 17, (1L << 17), red_cross, &data);

        mlx_loop(data.mlx);


    return (0);
}

