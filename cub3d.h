
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <mlx.h>
#include <fcntl.h>
#include "keys.h"
#include <math.h>
#include "getnextline/get_next_line.h"
#include "libft/libft.h"
#include "mlx/mlx.h"


#define RED 0xFF0000
#define WHITE 0xFFFAFA
#define YELLOW 0xFFDEAD
#define BLUE 0x00CCCC
#define GREEN 0Xbef574


typedef struct s_display
{
	char	*sprite_text;

	char	*north_text;
	char	*south_text;
	char	*east_text;
	char	*west_text;

	int		ceiling_rgb;
	int		floor_rgb;

}	t_display;


typedef struct s_text t_text;

typedef struct s_text
{
	void	*img;
	void	*imgaddr;
	int     bits_per_pixel;
    int     line_length;
    int     endian;
	int 	w;
	int		h;

	t_text 	*next;


}	t_text;



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

	double perpWallDist;


	int stepX;
	int stepY;

	int side;	 //was a NS or a EW wall hit?

// map
    char     **map;
	int		map_w;
	int 	map_h;
	int		map_s;
	int 	error;

//window
	int width;
    int height;
	int color;
	int minimap_size;
	int speed;
	int displaymap;

// colors
	t_display *info;
	t_text *t;

}   t_data;

int			ft_parse(int fd, t_data *data);
void    draw_tab(t_data *data);
void     set_map(t_data *data);
int     set_player(t_data *data);
void            my_mlx_pixel_put(t_data *data, int x, int y, int color);
void fill_black(t_data *data);
void fill_ceiling(t_data *data);
void fill_floor(t_data *data);
void 	bresenham(int xdep, int ydep, int xfin, int yfin, t_data *data);
void dda(t_data *data);

void checkmap(t_data *data);
int checkzero_letter(char c);
int		red_cross(t_data *data);
int error_message(int index);
