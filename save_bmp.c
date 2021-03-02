
#include "cub3d.h"


t_bmp	fill_header(t_data *data, int fd)
{
	t_bmp info;

	info.bmfh_type1 = 'B';
	info.bmfh_type2 = 'M';
	write(fd, "BM", 2);
	info.bmfh_size = 54 + (4 * data->width * data->height);
	write(fd, &info.bmfh_size, 4);
	printf ("size =  %d \n", info.bmfh_size );
	info.bmfh_reserved1 = 0;
	info.bmfh_reserved2 = 0;
	write(fd, &info.bmfh_reserved1, 2);
	write(fd, &info.bmfh_reserved2, 2);
	info.bmfh_offset = 54;
	write(fd, &info.bmfh_offset, 4);

	info.bmih_size = 40;
	write(fd, &info.bmih_size, 4);

	info.bmih_w = data->width;
		write(fd, &info.bmih_w, 4);

	info.bmih_h = data->height;
	write(fd, &info.bmih_h, 4);

	info.bmih_plane = 1;
	write(fd, &info.bmih_plane, 2);


	info.bmih_bpp = data->bits_per_pixel;
	write(fd, &info.bmih_bpp, 2);

	info.bmih_compression = 0;
	write(fd, &info.bmih_compression, 4);

	info.bmih_sizeimage = 0; // ou mettre la vraie taille ?
		write(fd, &info.bmih_sizeimage, 4);

	info.bi_pxpermeterx = 0;
	info.bi_pxpermetery = 0;
	info.bi_colorused = 0;
	info.bi_clrimp = 0;
	write(fd, "\0\0\0\0", 4);
		write(fd, "\0\0\0\0", 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, "\0\0\0\0", 4);




	//write(fd, &info, 54);

	int x = 0;
	int y = data->height - 1;
	unsigned int color = 0;

	while (y  >= 0 )
	{
		while(x < data->width)
		{
			color = ((unsigned int *)data->imgaddr)[(y * data->width) + x++];
			write(fd, &color, 3);
			write(fd, "\0", 1);

		}
		x = 0;
		y--;
	}
	return (info);

}

void 	save_bmp(t_data *data)
{
	int fd;
	t_bmp info;


	//On draw l'image dans les data
	fill_black(data);
	fill_ceiling(data);
	fill_floor(data);
	dda(data);

	//

	fd = open("test.bmp", O_CREAT | O_WRONLY);
	info = fill_header(data, fd);
	//write(fd, &info, 54);

}
