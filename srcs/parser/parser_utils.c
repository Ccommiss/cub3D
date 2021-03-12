#include "cub3d.h"


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
	if (sign == 'N' || sign == 'S' || sign == 'E' || sign == 'W')
	{
		if ((data->pos_x != -1 && data->pos_y != -1) && (data->pos_x != x + 0.5 || data->pos_y != y + 0.5 ))
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
