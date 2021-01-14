#include "cub3d.h"


int		red_cross(void)
{
	exit(0);
	return (0);
}

 int     close_window(t_data *data)
{
	(void)data;
 //   mlx_clear_window(data->mlx, data->win);
  //  mlx_destroy_window(data->mlx, data->win);
	exit(0);
    return (1);
}

 int   key_hook(int keycode, t_data *data)
 {
     printf("KEYCODE IS %d\n", keycode);
	 (void)data;
    // if (keycode == KEY_Q)
      //  clear_wind(data->mlx, data->win);
   // else
        printf("BAD KEYPRESS!\n");
    return (1);

 }

 void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->imgaddr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int mouse_move(int x, int y, t_data *data)
{
	int width;
	int height;
	static int i;
	i = 0;

	printf( "X %d AND Y %d AND I = %d !\n", x, y, i);
	if (i == 0)
	{
		i++;
		data->img = mlx_xpm_file_to_image(data->mlx, "mario.xpm", &width, &height);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);

	}
	else
	{
		my_mlx_pixel_put(data, x, y, 0x00FF0000);
		mlx_put_image_to_window(data->mlx, data->win, data->img2, 0, 0);
	}

	return (1);
}

int		mouse_hook(int button, int x, int y, t_data *data)
{
	int width;
	int height;
	static int i = 0;

	if (button == 1){
	printf( "BUTTON %d IS PRESSED !\n", button);
	printf( "X %d AND Y %d IS PRESSED !\n", x, y);
	printf( "I = %d !\n", i);
//	mouse_move(x, y, &data);

	if (i == 0){
		//mlx_destroy_image(data->mlx, data->img);
		// mlx_clear_window(data->mlx, data->win);
		my_mlx_pixel_put(data, x, y, 0x00FF0000);
		data->img = mlx_xpm_file_to_image(data->mlx, "mario.xpm", &width, &height);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 50, 50);
		i++;
	}
	else
	{
		//mlx_destroy_image(data->mlx, data->img);
	//	mlx_clear_window(data->mlx, data->win);
		my_mlx_pixel_put(data, x, y, 0x00FF0000);
		data->img = mlx_xpm_file_to_image(data->mlx, "beyonce.xpm", &width, &height);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 50, 50);
		i--;
	}
	//mlx_png_file_to_image(data->mlx, file, &width, &height);

	}
	return (0);

}



int main(void)
{
    t_data data;
	//int key_code;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 600, 500, "Hello world!");
	data.img = mlx_new_image(data.mlx, 600, 500);
	data.imgaddr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

    mlx_key_hook(data.win, key_hook, &data);
	mlx_hook(data.win, 6, 1L<<13, mouse_move, &data);
//	mlx_mouse_hook(data.win, mouse_hook, &data);
	mlx_hook(data.win, 6, 1L<<13, mouse_move, &data);
//	mlx_hook(data.win, 33, (1L << 17), close_window, &data);
//	mlx_hook(data.win, 33, (1L << 17), close_window, data.mlx);
	mlx_hook(data.win, 17, (1L << 17), red_cross, &data); //fonctionne


    mlx_loop(data.mlx);
    return (0);
}
