#include "cub3d.h"


void	*ft_realloc(void *ptr, size_t cursize, size_t newsize)
{
	void	*newptr;

	if (!ptr)
		return (malloc(newsize));
	newptr = malloc(newsize);
	ft_memset(newptr, '.', newsize);
	ft_memcpy(newptr, ptr, cursize);
	free(ptr);
	return (newptr);
}


int ft_parse(int fd, t_data *data)
{
	char *line = NULL;
	int x = 0;
	int y = 0;
	int i = 0;

	while (get_next_line(fd, &line))
	{
		data->map_h = y + 1;
		// on ajoute une case au double tab a chaque nvelle ligne lue
	//	printf ("REALLOCING BIG MAP TO ADD 1\n");
		data->map = (char **)ft_realloc(data->map, (data->map_h - 1)  * sizeof(char *), (data->map_h + 1) * sizeof(char *));
		data->map[data->map_h] = 0;

		// on malloc de la taille de la ligne
		if (data->map_w == 0 || ft_strlen(line) > (size_t)data->map_w)
		{
			if(!(data->map[y] = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1))))
				return (0);
			ft_memset(data->map[y], '.', ft_strlen(line) + 1);
		//	printf ("ALLOCING %lu to data->map[%d] \n", ft_strlen(line) + 1, y);
		}
		else
		{
			if(!(data->map[y] = (char *)malloc(sizeof(char) * (data->map_w + 1))))
				return (0);
			ft_memset(data->map[y], '.', data->map_w + 1);
		//	printf ("ALLOCING %d to data->map[%d] \n", data->map_w, y);
		}
		// on copie la ligne dans le tableau
		//printf("LINE = %s\n", line);
		while (*line)
		{
			data->map[y][x] = *line++;
			if (data->map[y][x] == 'N')
			{
				data->pos_x = x;
				data->pos_y = y;
			}
			x++;
		}
		data->map[y][x] = '\0';
		//printf("DATA MAP Y = %s\n", data->map[y]);
		//si jamais la ligne est  plus longue que les autres, sa longueur devient la nouvelle reference pour les autres
		if (x > data->map_w)
		{
			i = 0;
			// on realloue toutes les cases du tableau a la nouvelle taille de reference
			while (i < y)
			{
			//	printf ("REALLOCING data->map[%d]\n", i);
				// lancienne taille c data->mapw
				data->map[i] = (char *)ft_realloc(data->map[i], data->map_w, sizeof(char) * x + 1);
				data->map[i][data->map_w] = '\0';
				i++;
			}
			data->map_w = x;
		}
		y++;
		data->map[y] = 0;
		x = 0;
	}
	return 1;
}

