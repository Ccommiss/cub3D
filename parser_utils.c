#include "cub3d.h"

int ft_check_chars(char sign, t_data *data, int x, int y)
{
	//printf ("CHECKED SIGN %c \n", sign);
	if (sign == 'N' || sign == 'S' || sign == 'E' || sign == 'W')
	{
			printf ("%d x - %d y", x, y);
		printf("chek char x %f y %f \n", data->pos_x, data->pos_y);
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
