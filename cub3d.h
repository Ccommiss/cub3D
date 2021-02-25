
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

enum e_sides
{

	NORTH = 0,
	SOUTH,
	EAST,
	WEST
};

typedef struct s_spr t_spr;

typedef struct s_spr // list chainee 
{

	t_spr *head;
	int index; // a trier selon la distance

	double distance; // distance perp  au jouerur
	double x;		 // x du sprite
	double y;		 // y du sprite

	t_spr *next;

} t_spr;

typedef struct s_spr_geo
{
	double x;
	double y;
	double inv; 
	double trans_x;
	double trans_y;
	int screen_x;
	int height;
	int width;

} t_spr_geo;

typedef struct s_draw
{
	int start_x;
	int start_y;
	int end_x;
	int end_y;

	int tex_x;
	int tex_y;

	int pos;
	int y;
	unsigned int color;

} t_draw;

typedef struct s_display
{
	char *sprite_text;

	char *north_text;
	char *south_text;
	char *east_text;
	char *west_text;

	int ceiling_rgb;
	int floor_rgb;

} t_display;

typedef struct s_text t_text;

typedef struct s_text
{
	char side;
	void *img;
	void *imgaddr;
	int bits_per_pixel;
	int line_length;
	int endian;
	int w;
	int h;

	t_text *next;

} t_text;

typedef struct s_data
{
	void *mlx;
	void *win;
	void *img;
	void *imgaddr;
	int bits_per_pixel;
	int line_length;
	int endian;

	//Player

	double pos_x;
	double pos_y;
	double dirx;
	double diry;

	//vue
	double camera_x;
	double camera_y;
	double planeX;
	double planeY;

	// Rayon
	int map_x;
	int map_y;
	double raydir_x;
	double raydir_y;

	double dx; //offset to tile
	double dy;
	double delta_x; // space between next x and next next x
	double delta_y;

	double perpwalldist;

	int stepX;
	int stepY;

	int side; //was a NS or a EW wall hit?

	// map
	char **map;
	int map_w;
	int map_h;

	int map_s;
	int error;

	//window
	int width;
	int height;
	int color;
	int minimap_size;
	int speed;
	int displaymap;

	double *zbuffer; // a malloc

	// colors
	t_display *info;
	t_text *t;
	t_spr *spr;

	void *sprimg;
	void *sprimgaddr;
	int sprbpx;
	int spline;
	int end;
	int spw;
	int sph;

} t_data;

/*
 *  [init.c] Initialisation functions
 */

int init_struct(t_data *data);
void init_plane(t_data *data);
void init_base(t_data *data);
int loadimage(t_data *data);

/*
 *  [parser.c] Parsing functions
 */

int ft_parse(int fd, t_data *data);
void checkmap(t_data *data);
int checkzero_letter(char c);

int ft_check_chars(char sign, t_data *data, int x, int y);
int ft_mapcheck(char *str);
void ft_finddir(t_data *data, char dir) ;


/*
 *  [visu2d.c] Minimap fucntions
 */

void draw_tab(t_data *data);
void set_map(t_data *data);
int set_player(t_data *data);
void set_compass(t_data *data);

/*
 *  [display.c] Displaying fucntions
 */

void display(t_data *data);
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
void fill_black(t_data *data);
void fill_ceiling(t_data *data);
void fill_floor(t_data *data);

void sprite_drawing(t_data *data);
void sprite_casting(t_data *data);


int key_hook(int keycode, t_data *data);



void bresenham(int xdep, int ydep, int xfin, int yfin, t_data *data);
void dda(t_data *data);


int red_cross(t_data *data);
int error_message(t_data *data, int index);


