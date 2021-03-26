/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:53:32 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/25 08:49:57 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**  iscomplete
**
** 	[synopsis] : checks whether or not all infos have been read and set
** 	[call] : ft_parse
** 	[return] : 0 if is not complete, 1 if it is
*/

int	iscomplete(t_data *data)
{
	if (!data->height || !data->width || !data->info->west_text
		|| !data->info->east_text || !data->info->sprite_text
		|| !data->info->north_text || !data->info->south_text
		|| data->info->floor_rgb == -1 || data->info->ceiling_rgb == -1)
		return (0);
	return (1);
}

/*
**  ft_parse
**
** 	[synopsis] : reads line by line the file and parse it
** 		> ft_parse_info : parses the infos (colors, textures, etc)
** 		> ft_parse_map : parses the map and then fill data->map tab
** 		>
** 	[call] : in main
** 	[return] : 1 if success, exits if error occurs while parse_info/parse_map
*/

int	ft_parse(int fd, t_data *data)
{
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line) && data->error == 0)
	{
		if (!ft_isempty(line) && !iscomplete(data))
			ft_parse_info(data, line);
		else if (iscomplete(data) == 1)
			if (ft_parse_map(data, line) == -1)
				data->error = MALLOC_ERROR;
		free(line);
	}
	if (data->error == 0 && !ft_isempty(line) && iscomplete(data) == 1)
		ft_parse_map(data, line);
	free(line);
	if (data->error != 0)
		return (error_message(data, data->error));
	if (!iscomplete(data) || !data->map)
		return (error_message(data, MISSING_INFOS));
	if (data->pos_x < 0 || data->pos_y < 0)
		return (error_message(data, NO_PLAYER_FOUND));
	flood_fill(data);
	return (1);
}
