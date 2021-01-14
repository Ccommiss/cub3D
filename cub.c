#include "cub3d.h"

int		red_cross(void)
{
	exit(0);
	return (0);
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
    char    *dst;

    dst = data->imgaddr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
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

int     set_player(int x, int y, int width, int height, t_data *data)
{
    int xbis = x;
    int ybis = y;

        while (y < ybis + height)
       {
           while (x < xbis + width)
           {
               mlx_clear_window(data->mlx, data->win);
                my_mlx_pixel_put(data, x, y,  0xffd700);
                mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
                x++;
           }
           x = xbis;
           y++;
       }
       return 0;
}


 int   key_hook(int keycode, t_data *data)
 {
     printf("KEYCODE IS %d\n", keycode);
        if (keycode == KEY_UP)
            data->pos_y -= 4;
        if (keycode == KEY_DOWN)
             data->pos_y += 4;
        if (keycode == KEY_LEFT)
            data->pos_x -= 4;
         if (keycode == KEY_RIGHT)
            data->pos_x += 4;

        set_player(data->pos_x, data->pos_y, 10, 10, data);
        
        //    mlx_clear_window(data->mlx, data->win);
        //    fill_square(600, 500, data);
        //     set_player(data->pos_x, data->pos_y, 10, 10, data);
        //    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
       
      //  clear_wind(data->mlx, data->win);
   // else
        //printf("BAD KEYPRESS!\n");
    return (1);

 }


void    draw_tab(int tab[24][24], t_data *data)
{
    int i = 0;
    int j = 0;
    int x = 0;
    int y = 0;
   
        while (i < 24)
        {
            while (j < 24)
            {
                if (tab[i][j] > 0)
                    set_player(x, y, 10, 10, data);
                j++;
                y +=10;
            }
            j = 0;
            y = 0;
            i++;
            x += 10;
        }
}



int main(void)
{
    t_data data;
    int width = 600;
    int height = 500;

    int tab[24][24] = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
  

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, width, height, "who run the world ?");
	data.img = mlx_new_image(data.mlx, width, height);
	data.imgaddr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

    fill_square(width, height, &data);
   

    data.pos_x = 50;
    data.pos_y = 50;

//set_player(data.pos_x, data.pos_y, 10, 10, &data)
 
  //1events
  //2 draw according to events
  //3 render
   
        
        mlx_hook(data.win, 2, 1L<<0, key_hook, &data);
	    mlx_hook(data.win, 17, (1L << 17), red_cross, &data); //fonctionne
        draw_tab(tab, &data);
        //mlx_hook(data.win, 2, 1L<<0, set_player, &data);
        printf (" %d ___ %d  ",data.pos_x, data.pos_y);
        mlx_clear_window(data.mlx, data.win);
        mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
        mlx_loop(data.mlx);

       
    return (0);
}

