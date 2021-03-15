#include "cub3d.h"

/*
 *  ft_finddir
 *
 * 	[synopsis] : set the dirx & diry positions according to letter found in game
 * 	[return] : none
 */

void ft_finddir(t_data *data, char dir) //chamboule tout,marche pas avec autre config que W qui est le truc de base
{
	data->dirx = 0.0;
	data->diry = 0.0;
	if (dir == 'N')
		data->diry = -1;
	else if (dir == 'S')
		data->diry = 1;
	else if (dir == 'E')
		data->dirx = 1;
	else if (dir == 'W')
		data->dirx = -1;
}

/*
 *  load_sprite
 *
 * 	[synopsis] : set the dirx & diry positions according to letter found in game
 * 	[return] : none
 */

int load_sprite(t_data *data, int x, int y)
{
	static int i;

	if (!data->spr)
	{
		i = 0;
		data->spr = (t_spr *)malloc(sizeof(t_spr));
		if (!data->spr)
			return (error_message(data, 10));
		data->spr->head = data->spr;
	}
	else
	{
		data->spr->next = (t_spr *)malloc((sizeof(t_spr)));
		if (!data->spr->next)
			return (error_message(data, 10));
		data->spr->next->head = data->spr->head; //on sauvegarde la tete, ainsi chaque maillon contient le ptr vers le debut de la liste
		data->spr = data->spr->next;
	}
	data->spr->index = i++;
	data->spr->x = x;
	data->spr->y = y;
	data->spr->distance = 0;
	data->spr->next = NULL;
	return (1);
}

/*
 *  ft_realloc_tab
 *
 * 	[synopsis] : realloc all data->map[y] lines, in case a line is longer than the previous
 * 				ones
 * 	[return] : 1 if success, -1 if malloc fails
 */

int ft_realloc_tab(t_data *data, int x, int y)
{
	int i;
	i = 0;
	while (i < y)
	{
		data->map[i] = (char *)ft_realloc(data->map[i], data->map_w, sizeof(char) * x + 1);
		if (!data->map[i])
			return (close_win(data));
		data->map[i][data->map_w] = '\0';
		i++;
	}
	data->map_w = x;
	return (1);
}

/*
 *  fill_maptab
 *
 * 	[synopsis] : fill the data->map tab (char **map) with the line
 * 	[return] : 1 if success,
 */

int fill_maptab(t_data *data, char *line, int y)
{
	int x;
	int i;

	x = 0;
	i = 0;
	while (*line && data->error == 0)
	{
		if (ft_check_chars(*line, data, x, y) == -1)
			return (-1);
		else if (ft_check_chars(*line, data, x, y) == 1)
			data->map[y][x] = *line++;
		else if (ft_check_chars(*line++, data, x, y) == 2)
			data->map[y][x] = '0';
		x++;
	}
	data->map[y][x] = '\0';
	if (x > data->map_w)
		ft_realloc_tab(data, x, y);
	return (1);
}

int ft_parse_map(t_data *data, char *line)
{
	static int y;
	int len;

	if ((y == 0) && ft_isempty(line))
		return (0);
	if (data->map_h == 0)
		y = 0;
	data->map_h = y + 1;
	data->map = (char **)ft_realloc(data->map, (data->map_h) * sizeof(char *), (data->map_h + 1) * sizeof(char *));
	if (!data->map)
		return (close_win(data));
	data->map[data->map_h] = 0;
	if (data->map_w == 0 || ft_strlen(line) > (size_t)data->map_w)
		len = ft_strlen(line) + 1;
	else
		len = data->map_w + 1;
	data->map[y] = (char *)malloc(sizeof(char) * (len));
	if (!data->map[y])
		return (close_win(data));
	ft_bzero(data->map[y], len);
	fill_maptab(data, line, y);
	data->map[++y] = 0;
	return 1;
}

/*
 *  iscomplete
 *
 * 	[synopsis] : checks whether or not all infos have been read and set
 * 	[call] : ft_parse
 * 	[return] : 0 if is not complete, 1 if it is
 */

int iscomplete(t_data *data)
{
	if (!data->info->west_text || !data->info->east_text ||
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
 * 			> error 4 if map is found before all infos have been found
 * 			>
 */

int ft_parse(int fd, t_data *data)
{
	char *line;

	line = NULL;
	while (get_next_line(fd, &line) && data->error == 0)
	{
		if (ft_mapcheck(line) == 0 && !ft_isempty(line) && !iscomplete(data))
			ft_parse_info(data, line);
		else if (ft_mapcheck(line) == 1 && iscomplete(data) == 1)
			ft_parse_map(data, line);
		else if (!ft_isempty(line) && ft_mapcheck(line) == 1 && !iscomplete(data))
			return (error_message(data, 4));
		free(line);
	}
	if (ft_mapcheck(line) == 1  && iscomplete(data) == 1)
		ft_parse_map(data, line);
	free(line);
	if (!iscomplete(data))
		return (error_message(data, 4));
	if (data->error == 0 && (data->pos_x < 0 || data->pos_y < 0))
		return (error_message(data, 2));
	checkmap(data);
	flood_fill(data);
	return (1);
}
