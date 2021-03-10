#include "../includes/cub3d.h"

char * ft_trim_inside(char *str)
{
	char *strnew;
	int i;
	int j;

	i = 0;
	j = 0;

	strnew = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	ft_bzero(strnew, ft_strlen(str));
	while(str[j])
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


int ft_getrgb(t_data *data, char *rgb)
{
	char **block;
	int r;
	int g;
	int b;
	block = ft_split(rgb, ',');
	int j;
	j = -1;
	while (block[++j] != NULL)
		block[j] = ft_trim_inside(block[j]);
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
		printf ("freeing blocks in RGB %s \n", block[i]);
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
