#include "cub3d.h"

/*
 *  iscomplete
 *
 * 	[synopsis] : checks whether or not all infos have been read and set
 * 	[call] : ft_parse
 * 	[return] : 0 if is not complete, 1 if it is
 */

int iscomplete(t_data *data)
{
	if (!data->height || !data->width || !data->info->west_text || !data->info->east_text ||
		!data->info->sprite_text || !data->info->north_text || !data->info->south_text
		|| data->info->floor_rgb == -1 || data->info->ceiling_rgb == -1)
		return (0);
	return (1);
}

/*
 *  ft_parse
 *
 * 	[synopsis] : reads line by line the file and parse it
 * 		> ft_parse_info : parses the infos (colors, textures, etc)
 * 		> ft_parse_map : parses the map and then fill data->map tab
 * 		>
 * 	[call] : in main
 * 	[return] : 1 if success, exits if error occurs while parse_info/parse_map
 */

int ft_parse(int fd, t_data *data)
{
	char *line;

	line = NULL;
	while (get_next_line(fd, &line) && data->error == 0 )
	{
		printf ("l : %s \n", line);
		if (!ft_isempty(line) && !iscomplete(data))
			ft_parse_info(data, line);
		else if (iscomplete(data) == 1) // on a toutes les infos 
			ft_parse_map(data, line);
		free(line);
	}
	if (data->error == 0 && !ft_isempty(line) && iscomplete(data) == 1) // pour la derniere ligne 
		ft_parse_map(data, line);
	free(line);
	if (data->error != 0)
		return (error_message(data, data->error));
	if (!iscomplete(data))
		return (error_message(data, MISSING_INFOS));
	if (data->pos_x < 0 || data->pos_y < 0)
		return (error_message(data, NO_PLAYER_FOUND));
	flood_fill(data);
	return (1);
}
