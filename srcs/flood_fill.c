#include "../includes/cub3d.h"

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
		load_sprite(data, x, y);
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
	int i;
	
	i = 0;
	copymap = (char **)malloc((sizeof(char *)) * (data->map_h + 1));
	if (!copymap)
		return (close_win(data));
	while (i < data->map_h)
	{
		copymap[i] = (char *)malloc(10 * data->map_w);
		if (!copymap[i])
			return (free_copymap(i, &copymap, -1));
		//ft_bzero(copymap[i], data->map_w + 1);
		ft_memset(copymap[i], '.', data->map_w);
		i++;
	}
	check_borders(data, data->pos_x, data->pos_y, &copymap);
	free_copymap(data->map_h, &copymap, 1);
	if (data->error != 0)
		return (error_message(data, data->error));
	return (1);
}