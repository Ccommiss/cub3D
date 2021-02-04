#include "cub3d.h"

void *ft_realloc(void *ptr, size_t cursize, size_t newsize)
{
	void *newptr;

	if (!ptr)
		return (malloc(newsize));
	newptr = malloc(newsize);
	ft_memset(newptr, '.', newsize);
	ft_memcpy(newptr, ptr, cursize);
	free(ptr);
	return (newptr);
}

int ft_check_chars(char sign, t_data *data, int x, int y)
{
	if (sign == 'N' || sign == 'S' || sign == 'E' || sign == 'W')
	{
		data->pos_x = x;
		data->pos_y = y;
		return (1);
	}
	else if (sign == '0' || sign == '1' || sign == '2' || sign == ' ')
		return (1);
	else
	{
		printf("bad char found.\n");
		return (-1);
	}
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
		else
			return (-1);
		x++;
	}
	data->map[y][x] = '\0';
	//si jamais la ligne est  plus longue que les autres, sa longueur devient la nouvelle reference pour les autres
	if (x > data->map_w)
	{
		i = 0;
		// on realloue toutes les cases du tableau a la nouvelle taille de reference
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

int error_message(int index)
{
	if (index == 1)
		printf("Map is not closed (top or bottom). \n");
	if (index == 2)
		printf("Map is not closed (borders). \n");

	// if (index = 3)
	// if (index = 4)
	// if (index = 5)

	return (-1);
}

int close_check(t_data *data)
{
	int y = 0;
	int x = 0;

	printf ("map h %d \n", data->map_h);

	while (y < data->map_h)
	{
		while (x < data->map_w)
		{
			printf(" Y = %d __ X = %d \n", y, x);
			if ((y == 0 || y == data->map_h - 1)) //premiere et dernier(e ligne
			{
				if (ft_strlen(ft_strtrim(data->map[y], "1 ")) != 0) //s'il ny a pas que 0 ou 1 on ret
					return (error_message(1));
			}

			if ((x == 0 || data->map[y][x - 1] == ' ')) // condition du premier caractere de la ligne
			{
				printf("2/ testing map[%d][%d] = %c \n", y, x, data->map[y][x]);
				if (data->map[y][x] == '0')
					return (error_message(2));
				else if (data->map[y][x] == '1' && data->map[y][x + 1] != '1' && data->map[y + 1][x] != '1' && data->map[y + 1][x] != ' ')
					return (error_message(2));
			}
			if ((x == data->map_w || data->map[y][x + 1] == ' ')) // condition du dernier caractere de la ligne
			{
				printf("2/ testing map[%d][%d] = %c \n", y, x, data->map[y][x]);
				if (data->map[y][x] == '0')
					return (error_message(2));
				else if (data->map[y][x] == '1' && data->map[y][x + 1] != '1' && data->map[y + 1][x] != '1' && data->map[y + 1][x] != ' ')
					return (error_message(2));
			}
			x++;

		}
		y++;
		x = 0;
	}
		return 1;
}

// int close_check(t_data *data)
// {
// 	int x = 0;
// 	int y = 0;

// 	while(data->map[y][x] != '1')
// 		x++;


// 	if (data->map[y][x] == '1')
// 		if (x < data->map_w && data->map[y][x+1] == '1')
// 			x += 1;
// 		else if (y < data->map_h && data->map[y+1][x] == '1')
// 			y += 1;
// 		else if ()



// }

void LabelComponent(t_data *data, int* output, int labelNo, unsigned short x, unsigned short y)
{
	static int first = 0;
  int index = x + data->map_w * y;
  printf ("LABEL CO : index is %d \n", index);
  if (data->map[y][x] == '0') 
  	return;   /* This pixel is not part of a component */
    /* This pixel has already been labelled  */
	if (output[index] == 9)
		printf ("MAP IS CLOSED\n");
	if (output[index] != 0) 
  		return; 
	if (first != 0)
  		output[index] = labelNo;
	else if (first == 0)
	{
		output[index] = 9;
		first = 1;
	}


  /* Now label the 4 neighbours: */
  if (x > 0)        
  	LabelComponent(data, output, labelNo, x-1, y);   /* left  pixel */
  if (x < data->map_w-1)  
  	LabelComponent(data, output, labelNo, x+1, y);   /* right pixel */
  if (y > 0)        
  	LabelComponent(data, output, labelNo, x, y-1);   /* upper pixel */
  if (y < data->map_h-1) 
  	LabelComponent(data, output, labelNo, x, y+1);   /* lower pixel */
}

void LabelImage(t_data *data, int* output)
{
	
  int labelNo = 0;
  int x = -1;
  int y = 0;
  output = malloc(sizeof(int) * data->map_w * data->map_h);
  ft_memset(output, 0, sizeof(int) * data->map_h * data->map_w);
  int index = x + data->map_w * y;
  while (y < data->map_h)
  {  
    while(x < data->map_w)
    { 
		x++;
      index++;
	  printf ("index = %d\n", index);
	  printf ("x = %d\n", x);
      if (data->map[y][x] == '0') 
	  	continue;   /* This pixel is not part of a component */
      if (output[index] != 0) 
	  	continue;   /* This pixel has already been labelled  */
     
	  /* New component found */
      labelNo++;
      LabelComponent(data, output, labelNo, x, y);
	 // x++;
	 
    }
	printf ("y = %d\n", y);
	y++;
  }
  int o = 0;
  int k = 0;
  printf("%d \n", (x - 1) + data->map_w * (y-1));
  while (o < (x - 1) + data->map_w * (y - 1))
  {
	while (k++ < data->map_w)
	{
		printf ("%d ", output[o]);
		o++;
	}
	printf ("\n");
	k = 0;
  }
}


int ft_parse(int fd, t_data *data)
{
	char *line = NULL;
	printf("**PARSING**\n");

	while (get_next_line(fd, &line))
	{
		if (ft_mapcheck(line) == 0 && ft_strlen(ft_strtrim(line, " ")) != 0)
			ft_parse_info(data, line);
		else if (ft_strlen(ft_strtrim(line, " ")) != 0)
			parse_map(data, line);
	}

	printf("WIDTH = %d -- HEIGHT = %d  \n", data->width, data->height);
	printf("INFO %s\n", data->info->north_text);
	printf("INFO %s\n", data->info->south_text);
	printf("INFO %s\n", data->info->east_text);
	printf("INFO %s\n", data->info->west_text);
	// la map est en dernier dans la fichier

	checkmap(data);
	// if (close_check(data) < 0)
	// 	return (-1);
	int *output = NULL;
	LabelImage(data, output);

	return 1;
}
