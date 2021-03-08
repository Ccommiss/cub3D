#include "../includes/cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->imgaddr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	if (x >= 0 && x < data->width && y >= 0 && y < data->height)
		*(unsigned int *)dst = color;
}

void display_pos(t_data *data)
{
	char *stringX;
	char *stringY;
	char *posx;
	char *posy;

	posx = ft_ftoa(data->pos_x, 4);
	posy= ft_ftoa(data->pos_y, 4);
    stringX = ft_strjoin("X = ", posx);
    stringY = ft_strjoin("Y = ", posy);
	mlx_string_put(data->mlx, data->win, 30, data->height - 50, BLUE, stringX);
	mlx_string_put(data->mlx, data->win, 30, data->height - 25, BLUE, stringY);
	mlx_string_put(data->mlx, data->win, 0, 0, WHITE, "COUCOU");
	free(stringX);
	free(stringY);
	free(posx);
	free(posy);
}

void display(t_data *data)
{
	printf (" DISPLAY \n");

	fill_black(data);
		printf (" DISPLAY2 \n");

	fill_ceiling(data);
		printf (" DISPLAY 3\n");

	fill_floor(data);
			printf (" DISPLAY 4\n");

	dda(data);
			printf (" DISPLAY 5\n");

	if (data->displaymap == 1)
	{
		set_compass(data);
		set_map(data);
		set_player(data);
		data->color = 0xffffff;
		bresenham(data->pos_x * data->minimap_size + data->width / 4, data->pos_y * data->minimap_size + data->height * 0.7, (data->pos_x + data->dirx) * data->minimap_size + data->width / 4, (data->pos_y + data->diry) * data->minimap_size + data->height * 0.7, data);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	data->imgaddr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);


	display_pos(data);


}
