#include "cub3d.h"

void	*ft_realloc(void *ptr, size_t cursize, size_t newsize)
{
	void	*newptr;

	if (!ptr)
		return (malloc(newsize));
	newptr = malloc(newsize);
	ft_memset(newptr, '.', newsize);
	ft_memcpy(newptr, ptr, cursize);
	if (cursize != 0)
		free(ptr);
	return (newptr);
}

int	ft_check_chars(char sign, t_data *data, int x, int y)
{
	if (sign == 'N' || sign == 'S' || sign == 'E' || sign == 'W')
	{
		if ((data->pos_x != -1 && data->pos_y != -1)
			&& (data->pos_x != x + 0.5 || data->pos_y != y + 0.5))
			return (error_message(data, TWO_PLAYERS));
		data->pos_x = x + 0.5;
		data->pos_y = y + 0.5;
		ft_finddir(data, sign);
		return (2);
	}
	else if (ft_is_in_str("012 	", sign))
		return (1);
	return (error_message(data, 3));
}

int	ft_mapcheck(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 'N' && str[i] != 'S' && str[i] != 'E' && str[i] != 'W'
			&& str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != ' '
			&& str[i] != '	')
			return (0);
		i++;
	}
	return (1);
}

/*
**  ft_trim_inside
**
** 	[synopsis] : trims a str inside
** 	[call] : ft_get_rgb
** 	[return] : new str without blanks inside
*/

char	*ft_trim_inside(char *str)
{
	char	*strnew;
	int		i;
	int		j;

	i = 0;
	j = 0;
	strnew = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!strnew)
	{
		free(str);
		return (NULL);
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
**  ft_replace_tabs
**
** 	[synopsis] : replaces tabs (int 9) by spaces (int 32) in order to
** 				be able to format separators split later.
** 	[call] : ft_parse_infos
** 	[return] : none
*/

void	ft_replace_tabs(char **line)
{
	int	i;

	i = -1;
	while (line[0][++i])
	{
		if (line[0][i] == 9)
			line[0][i] = 32;
	}
}
