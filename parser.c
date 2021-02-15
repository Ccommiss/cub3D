#include "cub3d.h"


int error_message(int index)
{
	if (index == 1)
		printf("Map is not closed, blank was found in land or player is not inside the bounds. \n");
	if (index == 2)
		printf("No player found. \n");
	 if (index == 3)
	 	printf("Unexpected character found in map.\n");
	if (index == 4)
		printf("Missing infos.");
	// if (index = 5)

	return (-1);
}


void *ft_realloc(void *ptr, size_t cursize, size_t newsize)
{
	void *newptr;

	if (!ptr || ptr == NULL)
		return (malloc(newsize));
	newptr = malloc(newsize);
	ft_memset(newptr, '.', newsize);
	ft_memcpy(newptr, ptr, cursize);
	if (ptr != NULL)
		free(&ptr);
	return (newptr);
}

void	ft_finddir(t_data *data, char dir)
{
	data->dirX = 0;
	data->dirY = 0;

	if (dir == 'N')
		data->dirY = -1;
	else if (dir == 'S')
		data->dirY = 1;
	else if (dir == 'E')
		data->dirX = 1;
	else if (dir == 'W')
		data->dirX = -1;
}

int ft_check_chars(char sign, t_data *data, int x, int y)
{
	if (sign == 'N' || sign == 'S' || sign == 'E' || sign == 'W')
	{
		data->pos_x = x;
		data->pos_y = y;
		ft_finddir(data, sign);
		return (2);
	}
	else if (sign == '0' || sign == '1' || sign == '2' || sign == ' ')
		return (1);

	data->error = 3;
	printf("bad char found.\n");
	return (-1);

}

int ft_mapcheck(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 'N' && str[i] != 'S' && str[i] != 'E' && str[i] != 'W' &&
			str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int parse_map(t_data *data, char *line)
{
	int x = 0;
	static int y = 0;
	int i = 0;

	data->map_h = y + 1;
	// on ajoute une case au double tab a chaque nvelle ligne lue
	data->map = (char **)ft_realloc(data->map, (data->map_h - 1) * sizeof(char *), (data->map_h + 1) * sizeof(char *));
	data->map[data->map_h] = 0;
	// on malloc de la taille de la ligne
	if (data->map_w == 0 || ft_strlen(line) > (size_t)data->map_w)
	{
		if (!(data->map[y] = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1))))
			return (0);
		ft_memset(data->map[y], '.', ft_strlen(line) + 1);
	}
	else
	{
		if (!(data->map[y] = (char *)malloc(sizeof(char) * (data->map_w + 1))))
			return (0);
		ft_memset(data->map[y], '.', data->map_w + 1);
	}
	// on copie la ligne dans le tableau
	while (*line)
	{
		if (ft_check_chars(*line, data, x, y) == 1)
			data->map[y][x] = *line++;
		else if (ft_check_chars(*line++, data, x, y) == 2)
			data->map[y][x] = '0';
		else
			return (-1);
		x++;
	}
	data->map[y][x] = '\0';
	
	//si jamais la ligne est  plus longue que les autres, sa longueur devient la nouvelle reference pour les autres
	if (x > data->map_w)
	{
		i = 0; // on realloue toutes les cases du tableau a la nouvelle taille de reference
		while (i < y)
		{ // lancienne taille c data->mapw
			data->map[i] = (char *)ft_realloc(data->map[i], data->map_w, sizeof(char) * x + 1);
			data->map[i][data->map_w] = '\0';
			i++;
		}
		data->map_w = x;
	}
	y++;
	data->map[y] = 0;
	x = 0;
	return 1;
}

int ft_parse_info(t_data *data, char *line)
{
	char **block;
	printf("l: %s\n", line);
	block = ft_split(ft_strtrim(line, " "), ' ');
	if (block[0][0] == 'R')
	{
		data->width = ft_atoi(block[1]);
		data->height = ft_atoi(block[2]);
	}
	else if (ft_strncmp(block[0], "NO", 2) == 0)
		data->info->north_text = ft_strdup(block[1]);
	else if (ft_strncmp(block[0], "SO", 2) == 0)
		data->info->south_text = ft_strdup(block[1]);
	else if (ft_strncmp(block[0], "WE", 2) == 0)
		data->info->west_text = ft_strdup(block[1]);
	else if (ft_strncmp(block[0], "EA", 2) == 0)
		data->info->east_text = ft_strdup(block[1]);
	else if (ft_strncmp(block[0], "S", 1) == 0)
		data->info->sprite_text = ft_strdup(block[1]);
	return (1);
}




void check_borders(t_data *data, int x, int y, char ***mapbis)
{
	//int i = 0;
	// while (i < data->map_h)
	// {
	// 	printf("%s\n", mapbis[0][i]);
	// 	i++;
	// }
	// printf("\n**END MAP**\n");
	// printf("testing x = %d || y = %d \n", x, y);
	if (y < 0 || y >= data->map_h || x < 0 || x >= data->map_w || data->map[y][x] == ' ' || data->map[y][x] == '.')
	{
		data->error = 1;
		return;
	}
	if (data->map[y][x] == '1' || mapbis[0][y][x] == 'v')
		return;
	if (data->map[y][x] == '0' || data->map[y][x] == 'S' || data->map[y][x] == 'N'
	|| data->map[y][x] == 'E' || data->map[y][x] == 'W') //rajouter autres pos
		mapbis[0][y][x] = 'v';
	check_borders(data, x + 1, y, mapbis);
	check_borders(data, x - 1, y, mapbis);
	check_borders(data, x, y + 1, mapbis);
	check_borders(data, x, y - 1, mapbis);
	return;
}


int	iscomplete(t_data *data)
{
	//rajouter les RGB dans le parser avant de les mettre la
	if ( !data->info->west_text || !data->info->east_text ||
	!data->info->sprite_text || !data->info->north_text || !data->info->south_text)
		return 0;

	return 1;
}

int ft_parse(int fd, t_data *data)
{
	char *line = NULL;
	printf("**PARSING**\n");
	int info;
	info = 0;
	//data->map = NULL;

	while (get_next_line(fd, &line))
	{
		if (ft_mapcheck(line) == 0 && ft_strlen(ft_strtrim(line, " ")) != 0 && !iscomplete(data))
			ft_parse_info(data, line);
		else if (ft_strlen(ft_strtrim(line, " ")) != 0 && iscomplete(data) == 1)
			parse_map(data, line);
	}
		if (ft_mapcheck(line) == 0 && ft_strlen(ft_strtrim(line, " ")) != 0 && !iscomplete(data))
			ft_parse_info(data, line);
		else if (ft_strlen(ft_strtrim(line, " ")) != 0 && iscomplete(data) == 1)
			parse_map(data, line);
	if (data->error == 0 && (data->pos_x < 0 || data->pos_y < 0))
		data->error = 2;
	if (!iscomplete(data))
		data->error = 4;

	printf("WIDTH = %d -- HEIGHT = %d  \n", data->width, data->height);
	printf("INFO %s\n", data->info->north_text);
	printf("INFO %s\n", data->info->south_text);
	printf("INFO %s\n", data->info->east_text);
	printf("INFO %s\n", data->info->west_text);
	// la map est en dernier dans la fichier

	checkmap(data);

	char **copymap;
	int i = 0;
	copymap = (char **)malloc((sizeof(char *)) * (data->map_h + 1));
	while (i < data->map_h)
	{
		copymap[i] = (char *)malloc(10 * data->map_w);
		ft_bzero(copymap[i], data->map_w + 1);
		ft_memset(copymap[i], '.', data->map_w);
		//	printf("%s \n", copymap[i]);

		i++;
	}
	if (data->error == 0)
		check_borders(data, data->pos_x, data->pos_y, &copymap);
	if (data->error != 0)
		return (-1);
	return 1;
}
