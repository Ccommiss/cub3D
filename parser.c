#include "cub3d.h"

// int			ft_parse(int fd, t_data *data)
// {

// 	char *line = NULL;

// 	int x = 0;
// 	int y = 0;
// 	printf ("LA\n");
// 	data->map = (char **)malloc(sizeof(char *) * (200));
// 	while (get_next_line(fd, &line))
// 	{
// 		printf("line = %s\n", line);
// 		data->map[y] = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1 ));
// 		while (*line)
// 		{

// 			data->map[y][x] = *line++;
// 			if (data->map[y][x] == 'N')
// 			{
// 				data->pos_x = x;
// 				data->pos_y = y;
// 			}
// 			x++;
// 		}
// 		data->map[y][x] = '\0';
// 		//printf ("MAP X = %s\n", data->map[y]);
// 		y++;
// 		if (x > data->map_w)
// 			data->map_w = x;
// 		x = 0;
// 	}
// 	data->map_h = y;
// 	return 1;
// }

void *ft_realloc(void *ptr, size_t n)
{
	char **newptr;
	newptr = (char **)malloc((sizeof(char *) + 1) * n + 1);
	
	size_t i;
	i = 0;
	while (i++ < n)
		newptr[i][0] = ptr[i][0];
	free(ptr);
	//	ptr = (char **)malloc((sizeof(char *) + 1) * n);
	//ptr = tmp;
	//free(tmp);
	return (newptr);
}


int ft_parse(int fd, t_data *data)
{

	char *line = NULL;

	int x = 0;
	int y = 0;
	int n = 2;
	printf("LA\n");
	data->map = (char **)malloc(sizeof(char *) * 2); //init
	while (get_next_line(fd, &line))
	{
		data->map = (char **)ft_realloc(data->map, (n++ + 1) * sizeof(char *));
		//data->map = (char **)realloc(data->map, (n++ + 1) * sizeof(char *));
		printf("line = %s\n", line);
		data->map[y] = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
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
		printf ("MAP X = %s\n", data->map[y]);
		y++;
		if (x > data->map_w)
			data->map_w = x;
		x = 0;
	}
	data->map_h = y;

int i;
int j;
	 	for (i = 0; i < data->map_h; i++)		
 	{		
 		for (j = 0; j < data->map_w; j++)		
 		{		
 			printf("[%d][%d]", i, j);		
 			printf("%c ", data->map[i][j]);		
 		}		
 		printf("\n");		
 	}		
	return 1;
}