#include "cub3d.h"


int		red_cross(void)
{
	exit(0);
	return (0);
}


void checkmap(t_data *data)
{
	printf("[%d][%d]", data->map_w, data->map_h);
	int i;
	int j;
		for (i = 0; i < data->map_h; i++)
 	{
 		for (j = 0; j < data->map_w; j++)
 		{
			//printf("[%d][%d]\n", data->map_w, data->map_h);
 			printf("[%d][%d]", i, j);
 			printf("%c ", data->map[i][j]);
 		}
 		printf("\n");
 	}
}

void fill_black(t_data *data)
{
    int i = 0;
    int j = 0;

  while (i < data->height - 1)
       {
           while (j < data->width - 1)
           {
                my_mlx_pixel_put(data, j, i, 0x000000);
                j++;
           }
           j = 0;
           i++;
       }
}


void fill_ceiling(t_data *data)
{
    int i = 0;
    int j = 0;

  	while (i < data->height/2)
       {
           while (j < data->width)
           {
                my_mlx_pixel_put(data, j, i, BLUE);
                j++;
           }
           j = 0;
           i++;
       }
}

void fill_floor(t_data *data)
{
    int i = data->height/2;
    int j = 0;

  	while (i < data->height)
       {
           while (j < data->width)
           {
                my_mlx_pixel_put(data, j, i, GREEN);
                j++;
           }
           j = 0;
           i++;
       }
}



int     set_player(t_data *data)
{
    int w = 0;
    int h = 0;

    while (h++ < 3)
    {
        while (w++ < 3)
            my_mlx_pixel_put(data, (data->pos_x * data->minimap_size + w + data->width/4), (data->pos_y * data->minimap_size + h + data->height * 0.7),  BLUE);
		w = 0;
    }
    return (0);
}

void     set_map(t_data *data)
{
	int w;
	int h;
	int pixw;
	int pixh;

	w = 0;
	h = 0;
	pixw = 0;
	pixh = 0;

	//printf ("**SEETTING MAP OK**\n");

	while (h < data->map_h)
	{
		while (w < data->map_w)
		{
			if (checkzero_letter(data->map[h][w]) == 0)
			{
				pixh = data->minimap_size * h + data->height * 0.7; // data->height pour centrer
				while (pixh++ < data->minimap_size  * (h + 1) + data->height * 0.7)
				{
					pixw = data->minimap_size * (w) + (data->width/4) ;
					while (pixw++ < data->minimap_size  * (w + 1) + (data->width/4)) //pour mettre au milieu
						my_mlx_pixel_put(data, pixw, pixh, 0xffd700);
				}
			}
			w++;
		}
		h++;
		w = 0;
	}
}
