#include "../includes/cub3d.h"

int error_message(t_data *data, int index)
{
	if (data->error == 0)
	{
		printf("Error :\n");
		data->error = index;
		if (index == 1)
			printf("Map is not closed, blank was found in land or player is not inside the bounds. \n");
		if (index == 2)
			printf("No player found. \n");
		if (index == 3)
			printf("Unexpected character found in map.\n");
		if (index == 4)
			printf("Missing infos.");
		if (index == 5)
			printf("Two players found in map.\n");
		if (index == 6)
			printf("Texture reference could not be found.\n");
		if (index == 7)
			printf("Bad RGB color formatting.\n");
		if (index == 8)
			printf("RGB values can't be over 255 or below 0.\n");
	}
	if (data->t != NULL)
	{
		free_textures(data, data->t);
	}
	free_sprites(data);
	return (-1);
}

void *ft_realloc(void *ptr, size_t cursize, size_t newsize)
{
	void *newptr;

	printf("CURSIZE = %zu \n", cursize);
	printf("NEWSIZE = %zu \n", newsize);
	if (!ptr || ptr == NULL)
		return (malloc(newsize));
	newptr = malloc(newsize);
	printf("hey\n");
	ft_memset(newptr, '.', newsize);
	ft_memcpy(newptr, ptr, cursize);
	if (cursize != 0)
		free(ptr);
	return (newptr);
}

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


/// A FAIRE : REMPLACER TOUS LESTRIMS PAR DES ISEMPTY
int parse_map(t_data *data, char *line)
{
	static int y;

	if (data->map_h == 0)
		y = 0;

	printf("y = %d \n", y);
	data->map_h = y + 1;
	printf("MAP H = %d \n", data->map_h);
	printf("Current size = %lu \n", (data->map_h - 1) * sizeof(char *));
	data->map = (char **)ft_realloc(data->map, (data->map_h - 1) * sizeof(char *), (data->map_h + 1) * sizeof(char *));
	data->map[data->map_h] = 0;



	if ((y == 0) && ft_isempty(line))
		return 0;
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

int ft_getrgb(t_data *data, char *rgb)
{
	char **block;
	int r;
	int g;
	int b;
	block = ft_split(rgb, ',');
	printf("%s \n", block[0]);
	printf("%s \n", block[1]);
	printf("%s \n", block[2]);
	if (!block[0] || !block[1] || !block[2])
		return (error_message(data, 7));
	r = ft_atoi(block[0]);
	g = ft_atoi(block[1]);
	b = ft_atoi(block[2]);

	int i = 0;
	while (block[i] != NULL){
		printf ("freeing blocks in RGB \n");
		free(block[i++]);
	}
	free(block);
	free(rgb);

	if (r == 0 && g == 0 && b == 0)
		return (0x000000);
	else if (r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0)
		return (error_message(data, 8));
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

int ft_parse_info(t_data *data, char *line)
{
	char **block;
	char *newline;
	newline = ft_strtrim(line, " ");
	printf("l: %s\n", line);
	block = ft_split(newline, ' ');
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
	else if (ft_strncmp(block[0], "F", 1) == 0)
		data->info->floor_rgb = ft_getrgb(data, ft_strtrim(line, " F "));
	else if (ft_strncmp(block[0], "C", 1) == 0)
		data->info->ceiling_rgb = ft_getrgb(data, ft_strtrim(line, " C "));

	int i = 0;
	while(block[i] != NULL)
		free(block[i++]);
	free(block);
	free(newline);
	return (1);
}

int load_sprite(t_data *data, int x, int y)
{
	static int i = 0;

	if (!data->spr)
	{
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
