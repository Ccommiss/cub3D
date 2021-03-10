#include "../includes/cub3d.h"


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
	{
		while (i < y)
		{
			data->map[i] = (char *)ft_realloc(data->map[i], data->map_w, sizeof(char) * x + 1);
			data->map[i][data->map_w] = '\0';
			i++;
		}
		data->map_w = x;
	}
	return (1);
}


int parse_map(t_data *data, char *line)
{
	static int y;

	if (data->map_h == 0)
		y = 0;

	printf("y = %d \n", y);
	data->map_h = y + 1;
	printf("MAP H = %d \n", data->map_h);
	printf("Current size = %lu \n", (data->map_h - 1) * sizeof(char *));
	data->map = (char **)ft_realloc(data->map, (data->map_h) * sizeof(char *), (data->map_h + 1) * sizeof(char *));
	data->map[data->map_h] = 0;

	if ((y == 0) && ft_isempty(line))
		return (0);
	printf("before le IF \n");

	if (data->map_w == 0 || ft_strlen(line) > (size_t)data->map_w)
	{
		data->map[y] = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
		ft_memset(data->map[y], '.', ft_strlen(line) + 1);
	}
	else
	{
		data->map[y] = (char *)malloc(sizeof(char) * (data->map_w + 1));
		ft_memset(data->map[y], '.', data->map_w + 1);
	}
	if (!(data->map[y]))
		return (-1);
	fill_maptab(data, line, y);
	//si jamais la ligne est  plus longue que les autres, sa longueur devient la nouvelle reference pour les autres
	y++;
	data->map[y] = 0;
	return 1;
}



int load_sprite(t_data *data, int x, int y)
{
	static int i;

	if (!data->spr)
	{
		i = 0;
		data->spr = NULL;
		data->spr = (t_spr *)malloc(sizeof(t_spr));
		if (!data->spr)
			return (-1);
		data->spr->head = data->spr;
	}
	else
	{
		data->spr->next = (t_spr *)malloc((sizeof(t_spr)));
		if (!data->spr->next)
			return (-1);
		data->spr->next->head = data->spr->head; //on sauvegarde la tete, ainsi chaque maillon contient le ptr vers le debut de la liste
		data->spr = data->spr->next;
	}
	data->spr->index = i;
	data->spr->x = x;
	data->spr->y = y;
	data->spr->distance = 0;
	i++;
	data->spr->next = NULL;
	return (1);
}

void check_borders(t_data *data, int x, int y, char ***mapbis)
{
	if (y < 0 || y >= data->map_h || x < 0 || x >= data->map_w || data->map[y][x] == ' ' || data->map[y][x] == '.')
	{
		if (data->error == 0)
			error_message(data, 1);
		return;
	}
	if (data->map[y][x] == '1' || mapbis[0][y][x] == 'v')
		return;
	if (data->map[y][x] == '0' || data->map[y][x] == 'S' || data->map[y][x] == 'N' || data->map[y][x] == 'E' || data->map[y][x] == 'W') //rajouter autres pos
		mapbis[0][y][x] = 'v';
	if (data->map[y][x] == '2' && data->error == 0)
	{
		mapbis[0][y][x] = 'v';
		if (load_sprite(data, x, y) == -1) //si erreur de malloc
			data->error = 10;			   //si erreur de malloc
	}
	if (data->error == 0)
	{
		check_borders(data, x + 1, y, mapbis);
		check_borders(data, x - 1, y, mapbis);
		check_borders(data, x, y + 1, mapbis);
		check_borders(data, x, y - 1, mapbis);
	}
	return;
}

int iscomplete(t_data *data)
{
	if (!data->info->west_text || !data->info->east_text ||
		!data->info->sprite_text || !data->info->north_text || !data->info->south_text || data->info->floor_rgb == -1 || data->info->ceiling_rgb == -1)
		return (0);
	return (1);
}

int free_copymap(int nb_alloc, char ***copymap, int ret)
{
	int i;

	i = 0;
	while (i < nb_alloc)
		free(copymap[0][i++]);
	free(*copymap);
	return (ret);
}

int flood_fill(t_data *data)
{
	char **copymap;
	int i = 0;
	copymap = (char **)malloc((sizeof(char *)) * (data->map_h + 1));
	while (i < data->map_h)
	{
		copymap[i] = (char *)malloc(10 * data->map_w);
		if (!copymap[i])
			return (free_copymap(i, &copymap, -1));
		ft_bzero(copymap[i], data->map_w + 1);
		ft_memset(copymap[i], '.', data->map_w);
		i++;
	}
	check_borders(data, data->pos_x, data->pos_y, &copymap);
	free_copymap(data->map_h, &copymap, 0);
	if (data->error != 0)
		return (error_message(data, data->error));
	return (1);
}

int ft_parse(int fd, t_data *data)
{
	char *line = NULL;

	printf("**PARSING**\n");
	while (get_next_line(fd, &line) && data->error == 0)
	{
		if (ft_mapcheck(line) == 0 && !ft_isempty(line) && !iscomplete(data))
			ft_parse_info(data, line);
		else if (ft_mapcheck(line) == 1 && iscomplete(data) == 1)
			parse_map(data, line);
		free(line);
	}
	if (data->error != 0)
		return (error_message(data, data->error));
	if (!ft_isempty(line) && iscomplete(data) == 1)
		parse_map(data, line);
	if (!iscomplete(data))
		return (error_message(data, 4));
	if (data->error == 0 && (data->pos_x < 0 || data->pos_y < 0))
		return (error_message(data, 2));
	checkmap(data);
	flood_fill(data);
	free(line);
	return (1);
}
