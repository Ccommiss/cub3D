#include "cub3d.h"

int error_message(t_data *data, int index)
{
	printf("Error :\n");
	if (data->error == 0)
		data->error = index;
	if (data->error == MAP_NOT_CLOSED)
		printf("Map is not closed, blank was found in land or player is not inside the bounds. \n");
	if (data->error == NO_PLAYER_FOUND)
		printf("No player found. \n");
	if (data->error == UNEXPECTED_CHAR)
		printf("Unexpected character found in map.\n");
	if (data->error == MISSING_INFOS)
		printf("Missing infos.\n");
	if (data->error == TWO_PLAYERS)
		printf("Two players found in map.\n");
	if (data->error == TEXTURE_NOT_FOUND)
		printf("Texture reference could not be found.\n");
	if (data->error == BAD_RGB_FORMAT)
		printf("Bad RGB color formatting.\n");
	if (data->error == BAD_RGB_VALUES)
		printf("RGB values can't be over 255 or below 0.\n");
	if (data->error == REASSIGNATION)
		printf("Values can't be set up twice.\n");
	if (data->error == HEIGHT_WIDTH_NEG)
		printf("Height and width must be positive values.\n");
	if (data->error == 123)
		printf("Too many arguments.\n");
	close_win(data);
	return (-1);
}

void *ft_realloc(void *ptr, size_t cursize, size_t newsize)
{
	void *newptr;

	if (!ptr)
		return (malloc(newsize));
	newptr = malloc(newsize);
	ft_memset(newptr, '.', newsize);
	ft_memcpy(newptr, ptr, cursize);
	if (cursize != 0)
		free(ptr);
	return (newptr);
}

int ft_check_chars(char sign, t_data *data, int x, int y)
{
	//printf ("CHECKING SIGN = %c \n", sign);
	if (sign == 'N' || sign == 'S' || sign == 'E' || sign == 'W')
	{
		if ((data->pos_x != -1 && data->pos_y != -1) && (data->pos_x != x + 0.5 || data->pos_y != y + 0.5))
			return (error_message(data, 5));
		data->pos_x = x + 0.5;
		data->pos_y = y + 0.5;
		ft_finddir(data, sign);
		return (2);
	}
	else if (sign == '0' || sign == '1' || sign == '2' || sign == ' ' || sign == '	')
		return (1);
	printf("bad char found : %c at y %d x %d .\n", sign, x, y);
	return (error_message(data, 3));
}

int ft_mapcheck(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 'N' && str[i] != 'S' && str[i] != 'E' && str[i] != 'W' &&
			str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != ' ' && str[i] != '	')
			return (0);
		i++;
	}
	return (1);
}

/*
 *  ft_trim_inside
 *
 * 	[synopsis] : trims a str inside 
 * 	[call] : ft_get_rgb
 * 	[return] : new str without blanks inside
 */

char *ft_trim_inside(char *str)
{
	char *strnew;
	int i;
	int j;

	i = 0;
	j = 0;

	strnew = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!strnew)
	{
		free(str);
		return (NULL); //gerer erreur
	}
	ft_bzero(strnew, ft_strlen(str));
	while (str[j])
	{
		if (str[j] != ' ')
		{
			strnew[i] = str[j];
			i++;
		}
		j++;
	}
	strnew[i] = '\0';
	free(str);
	return (strnew);
}

/*
 *  ft_replace_tabs
 *
 * 	[synopsis] : replaces tabs (int 9) by spaces (int 32) in order to 
 * 				be able to format separators split later. 
 * 	[call] : ft_parse_infos
 * 	[return] : none
 */

void ft_replace_tabs(char **line)
{
	int i;

	i = -1;
	while (line[0][++i])
	{
		if (line[0][i] == 9)
			line[0][i] = 32;
	}
}