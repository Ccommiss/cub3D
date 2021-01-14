
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mlx.h>
#include <fcntl.h>
#include "keys.h"

typedef struct s_data
{
    void    *mlx;
    void    *win;
	void	*img;
	void	*img2;
	void	*imgaddr;
	int     bits_per_pixel;
    int     line_length;
    int     endian;

}   t_data;
