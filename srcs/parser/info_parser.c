#include "cub3d.h"


int ft_getrgb(t_data *data, char *rgb)
{
	char **block;
	int r;
	int g;
	int b;
	int j;

	r  = 0;
	g = 0;
	b = 0;
	block = ft_split(rgb, ',');
	j = -1;
	while (block[++j] != NULL)
		block[j] = ft_trim_inside(block[j]);
	if (block[0] && block[1] && block[2] && !block[3]) //si trop ou pas assez 
	{
		r = ft_atoi(block[0]);
		g = ft_atoi(block[1]);
		b = ft_atoi(block[2]);
	}
	else 
		data->error = BAD_RGB_FORMAT;
	ft_free_double_tab(block);
	free(rgb);
	if (r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0)
		data->error = BAD_RGB_VALUES;
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

/*
 *  isset 
 *
 * 	[synopsis] : verifies if a value has already been set before and prevent reassignation of value
 * 	[call] : ft_parse_infos
 * 	[return] : 0 if isn't set, 1 and set data->error if it is.
 */

int 	isset(t_data *data, int param)
{
	if ((param == north && !data->info->north_text) 
	|| (param == south && !data->info->south_text)
	|| (param == west && !data->info->west_text)
	|| (param == east && !data->info->east_text)
	|| (param == sprite && !data->info->sprite_text)
	|| (param == floor_rgb && data->info->floor_rgb == -1)
	|| (param == ceiling_rgb && data->info->ceiling_rgb == -1)
	|| (param == width && !data->width)
	|| (param == height && !data->height))
		return (0);
	printf ("PARAM = %d \n", param);
	data->error = REASSIGNATION;
	return(1);

}

// trouver un moyen si y a trop d'arguments genre deux paths par ex 

int ft_parse_info(t_data *data, char *line)
{
	char **block;
	char *newline;
	newline = ft_strtrim(line, " 	");
	ft_replace_tabs(&newline);
	block = ft_split(newline, ' ');
	if (!block[0] || !block[1])
		data->error = MISSING_INFOS; // missing infos 
	if (block[0][0] == 'R' && block[1] && block[2])
	{
		data->width = ft_atoi(block[1]);
		data->height = ft_atoi(block[2]);
		if (data->height <= 0 || data->width <= 0)
			data->error = HEIGHT_WIDTH_NEG; 
	}
	else if (ft_strncmp(block[0], "NO", 3) == 0 && !isset(data, north))
		data->info->north_text = ft_strdup(block[1]);
	else if (ft_strncmp(block[0], "SO", 3) == 0 && !isset(data, south))
		data->info->south_text = ft_strdup(block[1] );
	else if (ft_strncmp(block[0], "WE", 3) == 0  && !isset(data, west))
		data->info->west_text = ft_strdup(block[1]);
	else if (ft_strncmp(block[0], "EA", 3) == 0 && !isset(data, east))
		data->info->east_text = ft_strdup(block[1] );
	else if (ft_strncmp(block[0], "S", 3) == 0 && !isset(data, sprite))
		data->info->sprite_text = ft_strdup(block[1] );
	else if (ft_strncmp(block[0], "F", 2) == 0 && !isset(data, floor_rgb))
		data->info->floor_rgb = ft_getrgb(data, ft_strtrim(line, " F "));
	else if (ft_strncmp(block[0], "C", 2) == 0 && !isset(data, ceiling_rgb))
		data->info->ceiling_rgb = ft_getrgb(data, ft_strtrim(line, " C ")); 
	ft_free_double_tab(block);
	free(newline);
	return (1);
}
