#include "cub3d.h"


void fill_black(t_data *data)
{
    int i = 0;
    int j = 0;

  while (i < data->height)
       {
           while (j < data->width)
           {
                my_mlx_pixel_put(data, j, i, 0x000000);
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

    while (h++ < 10)
    {
        while (w++ < 10)
            my_mlx_pixel_put(data, (data->pos_x * 64 + w), (data->pos_y * 64 + h),  0x4b0082);
		w = 0;
		printf ("h %d", h);
    }
    printf ("POS X %f", data->pos_x);
    return 0;
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
	while (h < data->map_h)
	{
		while (w < data->map_w)
		{
			if (data->map[h][w] != '0')
			{
				pixh = 64*h;
				while (pixh++ < 64 * (h + 1))
				{
					pixw = 64 * (w);
					while (pixw++ < 64 * (w + 1))
						my_mlx_pixel_put(data, pixw, pixh, 0xffd700);
				}
			}
			w++;
		}
		h++;
		w = 0;
	}
}