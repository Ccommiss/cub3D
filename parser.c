#include "cub3d.h"

int			ft_parse(int fd, t_data *data)
{

	char *line = NULL;

	int x = 0;
	int y = 0;
	printf ("LA\n");
	data->map = (char **)malloc(sizeof(char *) * (300));
	while (get_next_line(fd, &line))
	{
		printf ("la\n");
		printf("line = %s\n", line);
		data->map[y] = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1 ));
		while (*line){

			data->map[y][x] = *line++;
			if (data->map[y][x] == 'N')
			{
				data->pos_x = x;
				data->pos_y = y;
			}
			x++;
		}
		data->map[y][x] = '\0';
		//printf ("MAP X = %s\n", data->map[y]);
		y++;
		if (x > data->map_w)
			data->map_w = x;
		x = 0;
	}
	data->map_h = y;

	return 1;
}

