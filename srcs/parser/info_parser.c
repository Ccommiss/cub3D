/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:48:14 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/17 18:36:55 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rgb_convert(char **block, int *r, int *g, int *b)
{
	*r = ft_atoi(block[0]);
	*g = ft_atoi(block[1]);
	*b = ft_atoi(block[2]);
}

int		ft_getrgb(t_data *data, char *rgb)
{
	char	**block;
	int		r;
	int		g;
	int		b;
	int		j;

	block = ft_split(rgb, ',');
	r = 0;
	g = 0;
	b = 0;
	j = -1;
	while (block[++j] != NULL)
		block[j] = ft_trim_inside(block[j]);
	if (!block[j])
		data->error = MALLOC_ERROR;
	if (block[0] && block[1] && block[2] && !block[3])
		rgb_convert(block, &r, &g, &b);
	else if (data->error == 0)
		data->error = BAD_RGB_FORMAT;
	if (r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0)
		data->error = BAD_RGB_VALUES;
	ft_free_double_tab(block);
	free(rgb);
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

/*
**  isset
**
** 	[synopsis] : verifies if a value has already been set before and prevent
**	reassignation of value
** 	[call] : ft_parse_infos
** 	[return] : 0 if isn't set, 1 and set data->error if it is.
*/

int		isset(t_data *data, int param)
{
	if ((param == north && !data->info->north_text)
	|| (param == south && !data->info->south_text)
	|| (param == west && !data->info->west_text)
	|| (param == east && !data->info->east_text)
	|| (param == sprite && !data->info->sprite_text)
	|| (param == ground && data->info->floor_rgb == -1)
	|| (param == ceiling && data->info->ceiling_rgb == -1)
	|| (param == width && !data->width)
	|| (param == height && !data->height))
		return (0);
	data->error = REASSIGNATION;
	return (1);
}

void	get_resolution(char **block, t_data *data)
{
	// int width;
	// int height;

	data->width = ft_atoi(block[1]);
	data->height = ft_atoi(block[2]);
	if (data->height <= 0 || data->width <= 0)
		data->error = HEIGHT_WIDTH_NEG;
	// mlx_get_screen_size(data->mlx, &width, &height);
	// if (data->width > width)
	// 	data->width = width;
	// if (data->height > height)
	// 	data->height = height;
}

int		ft_parse_info(t_data *data, char *line)
{
	char **block;
	char *newline;

	newline = ft_strtrim(line, " 	");
	ft_replace_tabs(&newline);
	block = ft_split(newline, ' ');
	if (ft_strncmp(block[0], "R", 2) == 0 && block[1] && block[2])
		get_resolution(block, data);
	else if (!ft_strncmp(block[0], "NO", 3) && block[1] && !isset(data, north))
		data->info->north_text = ft_strdup(block[1]);
	else if (!ft_strncmp(block[0], "SO", 3) && block[1] && !isset(data, south))
		data->info->south_text = ft_strdup(block[1]);
	else if (!ft_strncmp(block[0], "WE", 3) && block[1] && !isset(data, west))
		data->info->west_text = ft_strdup(block[1]);
	else if (!ft_strncmp(block[0], "EA", 3) && block[1] && !isset(data, east))
		data->info->east_text = ft_strdup(block[1]);
	else if (!ft_strncmp(block[0], "S", 3) && block[1] && !isset(data, sprite))
		data->info->sprite_text = ft_strdup(block[1]);
	else if (!ft_strncmp(block[0], "F", 2) && block[1] && !isset(data, ground))
		data->info->floor_rgb = ft_getrgb(data, ft_strtrim(line, " F "));
	else if (!ft_strncmp(block[0], "C", 2) && block[1] && !isset(data, ceiling))
		data->info->ceiling_rgb = ft_getrgb(data, ft_strtrim(line, " C "));
	ft_free_double_tab(block);
	free(newline);
	return (1);
}
