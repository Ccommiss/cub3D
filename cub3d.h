
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mlx.h>
#include <fcntl.h>
#include "keys.h"
#include <math.h>
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

    double     pos_x;
    double     pos_y;
	double		dirX;
	double		dirY;

	float	angle; //teta





//vue
	double cameraX;
	double cameraY;
	double planeX;
	double planeY;

// Rayon
	int mapX;
	int mapY;
	double rayDirX;
	double rayDirY;

	double dx; //offset to tile
	double dy;
	double	delta_x; // space between next x and next next x
	double	delta_y;

	int perpWallDist;


	int stepX;
	int stepY;

	int side;	 //was a NS or a EW wall hit?



// map
    char     **map;
	int		map_w;
	int 	map_h;
	int		map_s;

//window
	int width;
    int height;

	int color;
}   t_data;

int			ft_parse(int fd, t_data *data);
void    draw_tab(t_data *data);
void     set_map(t_data *data);
int     set_player(t_data *data);
void            my_mlx_pixel_put(t_data *data, int x, int y, int color);
void fill_black(t_data *data);
void 	bresenham(int xdep, int ydep, int xfin, int yfin, t_data *data);
