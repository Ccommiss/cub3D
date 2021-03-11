
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <mlx.h>
#include <fcntl.h>

#include "../mlx/mlx.h"
#include "keys.h"
//#include "key_linux.h"
//#include "../mlx_linux/mlx.h"


#include <math.h>
#include "../libft/libft.h"

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

enum e_pt
{
	X = 0,
	Y = 1
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


typedef struct s_bresenham
{
	int pt1[2]; // pourmettre le x et le y 
	int pt2[2]; //idem 0 = x 1 = y;

	unsigned int dx;
	unsigned int dy;

} t_bresenham;





typedef struct s_bmp
{

	// BitMapFileHeader
	char bmfh_type1;		  // "BM"
	char bmfh_type2;
	int bmfh_size;			  // size of file in bytes
	short int bmfh_reserved1; //2 bytes
	short int bmfh_reserved2;
	int bmfh_offset;		  //offset from beggining of file, 1078

	// BitMapInfoHeader
	int bmih_size;		  // size of bitmapinfoh
	int bmih_w;			  //img width
	int bmih_h;			  //img height
	short int bmih_plane; // must be set to 0 (??)
	short int bmih_bpp;	  //bitsperpixel, 24 for 16M colors
	int bmih_compression; //set to 0;
	int bmih_sizeimage;	  //size of the image data, in bytes.
	int bi_pxpermeterx;	  //set to 0
	int bi_pxpermetery;	  //idem
	int bi_colorused;	  //specifies the number of colors used in the bitmap, if set to zero the number of colors is calculated using the biBitCount member.
	int bi_clrimp;		  // 0 if all important

	char padding[24];


	void *image_data; // ????an array of
						//bytes that defines the bitmap bits. These are the actual image data, represented by consecutive rows, or "scan lines," of the bitmap. Each scan line consists of consecutive bytes representing the pixels in the scan line, in left-to-right order. The system maps pixels beginning with the bottom scan line of the rectangular region and ending with the top scan line.



} t_bmp;

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
void ft_finddir(t_data *data, char dir);

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
void display_pos(t_data *data);


void sprite_drawing(t_data *data);
void sprite_casting(t_data *data);

int key_hook(int keycode, t_data *data);

void bresenham(t_bresenham *b, t_data *data);
void dda(t_data *data);


int free_textures(t_data *data, t_text *head);
int free_sprites(t_data *data);
int flood_fill(t_data *data);
int load_sprite(t_data *data, int x, int y);



void 	save_bmp(t_data *data);
void *ft_realloc(void *ptr, size_t cursize, size_t newsize);
int ft_parse_info(t_data *data, char *line);


int red_cross(t_data *data); //free
int free_game(t_data *data);
int close_win(t_data *data); //close
int error_message(t_data *data, int index);
