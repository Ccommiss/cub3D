
#include "cub3d.h"


t_bmp	fill_header(t_data *data)
{
	t_bmp info;

	info.bmfh_type1 = 'B';
	info.bmfh_type1 = 'M';
	info.bmfh_size = 8;
	info.bmfh_reserved1 = 0;
	info.bmfh_reserved2 = 0;
	info.bmfh_offset = 54;

	info.bmih_size = 40;
	info.bmih_w = data->width;
	info.bmih_h = data->height;
	info.bmih_plane = 1;
	info.bmih_bpp = data->bits_per_pixel;
	info.bmih_compression = 0;
	info.bmih_sizeimage = 0; //4 * info.bmih_h * info.bmih_w;	  //size of the image data, in bytes.
	info.bi_pxpermeterx = 0;
	info.bi_pxpermetery = 0;
	info.bi_colorused = 256;
	info.bi_clrimp = 0;

	info.clr_r = 0;
	info.clr_g = 0;
	info.clr_b = 0;
	info.clr_res = 0;

	return (info);

}

void 	save_bmp(t_data *data)
{
	dda(data);

	int fd;
	t_bmp info;


	//file = fopen("test.bmp", "w");
	fd = open("test.bmp", O_CREAT | O_WRONLY);
	info = fill_header(data);
	write(fd, (void *)info, 448);

}
