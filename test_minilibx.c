#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <mlx.h> 
#include "cub3d.h"

 
 int     clear_wind(void *init, t_data *win)
{
    mlx_clear_window(init, win);    
    mlx_destroy_window(init, win);
    return (1);

}

 int   key_hook(int keycode, t_data *data)
 {
     printf("KEYCODE IS %d\n", keycode);
     if (keycode == 12)
        clear_wind(data->mlx, data->win);
    else 
        printf("BAD KEYPRESS!\n"); 
    return (1);
     
 }




int main(void)
{
    t_data data;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 1920, 1080, "Hello world!");
    mlx_key_hook(data.win, key_hook, &data);
    mlx_loop(data.mlx);
    return (0);
}