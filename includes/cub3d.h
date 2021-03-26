/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 21:18:38 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/25 21:24:30 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "keys.h"
# include "../libft/libft.h"
//  #include "key_linux.h"
//  #include "../mlx_linux/mlx.h"

# define RED 0xFF0000
# define WHITE 0xFFFAFA
# define YELLOW 0xFFDEAD
# define BLUE 0x00CCCC
# define GREEN 0Xbef574
# define GRASS 0x99e599
# define GREY 0X696969
# define LIGHTGREY 0X9A9A9A
# define VINTAGE_YELLOW 0Xe7cf8a
# define BLACK 0X303030

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

enum e_dir
{
	LEFT = 10,
	RIGHT,
	UP,
	DOWN
};

enum e_param
{
	north,
	south,
	west,
	east,
	sprite,
	ground,
	ceiling,
	width,
	height
};

enum e_errors
{
	MAP_NOT_CLOSED = 1,
	NO_PLAYER_FOUND,
	UNEXPECTED_CHAR,
	MISSING_INFOS,
	TWO_PLAYERS,
	TEXTURE_NOT_FOUND,
	BAD_RGB_FORMAT,
	BAD_RGB_VALUES,
	REASSIGNATION,
	HEIGHT_WIDTH_NEG,
	CANNOT_READ_FILE,
	BAD_FILENAME,
	TOO_MANY_ARGUMENTS,
	NO_FILE,
	MALLOC_ERROR
};

typedef struct s_spr	t_spr;

typedef struct s_spr
{
	t_spr	*head;
	int		index;
	double	distance;
	double	x;
	double	y;
	t_spr	*next;
}	t_spr;

typedef struct s_spr_geo
{
	double	x;
	double	y;
	double	inv;
	double	trans_x;
	double	trans_y;
	int		screen_x;
	int		height;
	int		width;
}	t_spr_geo;

typedef struct s_draw
{
	int				start_x;
	int				start_y;
	int				end_x;
	int				end_y;
	int				tex_x;
	int				tex_y;
	int				pos;
	int				y;
	unsigned int	color;

}	t_draw;

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

typedef struct s_text	t_text;

typedef struct s_text
{
	char	side;
	void	*img;
	void	*imgaddr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		w;
	int		h;
	t_text	*next;
}	t_text;

typedef struct s_bresenham
{
	int				pt1[2];
	int				pt2[2];
	unsigned int	dx;
	unsigned int	dy;
}	t_bresenham;

typedef struct s_visu2d
{
	int		w;
	int		h;
	int		pixw;
	int		pixh;
	int		center_w;
	int		center_h;
	double	init_w;
	double	init_h;
	int		move;
}	t_visu2d;

/*
**  < struct > t_bmp
**
** 	[synopsis] : used to save file as a .bmp file
**		> Bmfh = BitMap File Header
**		> Bmih = BitMap Info Header
**		> image data = the actual data of image pixel per pixel
** 	[return] : none
*/

typedef struct s_bmp
{
	char		bmfh_type1;
	char		bmfh_type2;
	int			bmfh_size;
	short int	bmfh_reserved1;
	short int	bmfh_reserved2;
	int			bmfh_offset;
	int			bmih_size;
	int			bmih_w;
	int			bmih_h;
	short int	bmih_plane;
	short int	bmih_bpp;
	int			bmih_compression;
	int			bmih_sizeimage;
	int			bi_pxpermeterx;
	int			bi_pxpermetery;
	int			bi_colorused;
	int			bi_clrimp;
	char		padding[24];
	void		*image_data;
}	t_bmp;

typedef struct s_img_data
{
	void	*img_ptr;
	void	*img_infos;
	int		endian;
	int		bpp;
	int		width;
	int		height;
	int		sl;
	int		color;
}	t_img_data;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*imgaddr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
	int			color;
	double		pos_x;
	double		pos_y;
	double		dirx;
	double		diry;
	double		speed;
	double		camera_x;
	double		camera_y;
	double		planeX;
	double		planeY;
	int			map_x;
	int			map_y;
	double		raydir_x;
	double		raydir_y;
	double		dx;
	double		dy;
	double		delta_x;
	double		delta_y;
	double		perpwalldist;
	int			stepx;
	int			stepy;
	int			side;
	int			hit;
	char		**map;
	int			map_w;
	int			map_h;
	int			error;
	int			minimap_size;
	int			displaymap;
	double		look;
	double		jump;
	double		*zbuffer;
	t_display	*info;
	t_text		*t;
	t_spr		*spr;
	t_visu2d	v;
	t_img_data	compass;
	t_img_data	map_icon;
	t_img_data	player;
	void		*sprimg;
	void		*sprimgaddr;
	int			sprbpx;
	int			spline;
	int			end;
	int			spw;
	int			sph;
}	t_data;

/*
**  [MAIN] Main functions
**		> main.c
**		>
*/

void	init_base(t_data *data);
int		check_format(char *name, t_data *data);
int		check_extension(char *filename);
int		init_struct(t_data *data);
void	init_plane(t_data *data);
int		loadimage(t_data *data);

/*
 *  [PARSER] Parsing functions
 */

int		ft_parse(int fd, t_data *data);
int		ft_parse_info(t_data *data, char *line);
void	get_resolution(char **block, t_data *data);
int		isset(t_data *data, int param);
int		ft_getrgb(t_data *data, char *rgb);
int		rgb_convert(char **block, int *r, int *g, int *b);
int		iscomplete(t_data *data);
int		ft_parse_map(t_data *data, char *line);
int		fill_maptab(t_data *data, char *line, int y);
int		ft_realloc_tab(t_data *data, int x, int y);
int		ft_check_chars(char sign, t_data *data, int x, int y);
int		ft_mapcheck(char *str);
void	ft_finddir(t_data *data, char dir);
int		flood_fill(t_data *data);
void	check_borders(t_data *data, int x, int y, char ***mapbis);
int		load_sprite(t_data *data, int x, int y);
int		free_copymap(int nb_alloc, char ***copymap, int ret);
void	*ft_realloc(void *ptr, size_t cursize, size_t newsize);
char	*ft_trim_inside(char *str);
void	ft_replace_tabs(char **line);
char	*ft_trim_inside(char *str);

/*
**  [RAYCAST] Displaying functions
*/

void	wall_casting(t_data *data);
void	calculate_step(t_data *data);
void	hit_check(t_data *data);
void	perpendicular_ray(t_data *data);
void	sprite_casting(t_data *data);

/*
**  [DISPLAY] Displaying functions
*/

int		display(t_data *data);
void	fill_black(t_data *data);
void	fill_ceiling(t_data *data);
void	fill_floor(t_data *data);
void	bresenham(t_bresenham *b, t_data *data);
void	define_move(t_data *data);
void	set_map(t_data *data);
void	set_compass(t_data *data);
void	set_needle(t_data *data);
void	set_player(t_data *data);
void	set_mapicon(t_data *data);
void	display_pos(t_data *data);
void	init_minimap(t_data *data);
void	items_color(t_data *data, t_visu2d *v);
void	map_background(t_data *data);
void	init_compass(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	wall_drawing(t_data *data, int x);
void	sprite_drawing(t_data *data);
void	save_bmp(t_data *data);

/*
 *  [EXIT]  exit function
 */

int		close_win(t_data *data); //close
int		free_game(t_data *data);
int		error_message(t_data *data, int index);
int		free_textures(t_data *data, t_text *head);
int		free_sprites(t_data *data);

/*
 *  [EVENTS]
 * 		> events.c
 * 		> move_events.c
 * 		> minimap_settings.c
 */

int		key_hook(int keycode, t_data *data);
int		speed_hook(int keycode, t_data *data);
int		is_zero(char c);
void	move_leftright(int keycode, t_data *data, int sec_spd, int sec_oth);
void	move_updown(int keycode, t_data *data, int sec_spd, int sec_oth);
void	minimap_settings(int keycode, t_data *data);

#endif
