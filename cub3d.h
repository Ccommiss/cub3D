
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mlx.h>
#include <fcntl.h>
#include "keys.h"
#include "getnextline/get_next_line.h"

typedef struct s_data
{
    void    *mlx;
    void    *win;
	void	*img;
	void	*imgaddr;
	int     bits_per_pixel;
    int     line_length;
    int     endian;

//Player

    int     pos_x;
    int     pos_y;

// map
    char     **map;
	int		map_w;
	int 	map_h;

//window
	int width;
    int height;

}   t_data;

int			ft_parse(int fd, t_data *data);
void    draw_tab(t_data *data);
