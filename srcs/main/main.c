/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:18:00 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/18 12:28:46 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	check_extension
**
** 	[synopsis] : checks if the filename is correct i.e. ends with .cub
**  [call] : in chek_format
**	[return] : 1 if ends with .cub, 0 if not
*/

int		check_extension(char *filename)
{
	int len;

	len = ft_strlen(filename);
	if (len != 0 && filename[len - 1] == 'b' && filename[len - 2] == 'u' && 
	filename[len - 3] == 'c' && filename[len - 4] == '.')
		return (1);
	return (0);
}

/*
**	check_format
**
** 	[synopsis] : checks if 
**		> the filename is correct i.e. ends with .cub
**		> we can read the file
**  [call] : in main
**	[return] : fd
*/

int		check_format(char *name, t_data *data)
{	
	int test;
	int fd;
	
	data->error = 0;
	if (!name)
		error_message(data, NO_FILE);
	if (!check_extension(name))
		error_message(data, BAD_FILENAME);
	fd = open(name, O_RDONLY);
	test = read(fd, 0, 0);
	if (test < 0)
		error_message(data, CANNOT_READ_FILE);
	return (fd);
}


int check_bmp(t_data *data, int argc, char **argv)
{
	if (argc > 3)
		error_message(data, TOO_MANY_ARGUMENTS);
	else if (argc == 3 && ft_strncmp(argv[2], "--save", 7) != 0)
		error_message(data, TOO_MANY_ARGUMENTS);
	return(1);
}

int		main(int argc, char **argv)
{
	t_data		data;
	t_display	info;
	int			fd;

	data.info = &info;
	init_base(&data);
	fd = check_format(argv[1], &data);
	check_bmp(&data, argc, argv);
	ft_parse(fd, &data);
	init_struct(&data);
	if (argc == 3 && ft_strncmp(argv[2], "--save", 7) == 0)
		save_bmp(&data);
	display(&data);
	mlx_hook(data.win, KEY_PRESS, 1L << 0, key_hook, &data);
	mlx_hook(data.win, KEY_RELEASE, 1L << 0, speed_hook, &data); //retour normal
	mlx_hook(data.win, 9, 1L << 21, display, &data);
	mlx_hook(data.win, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, close_win, &data);
	mlx_loop(data.mlx);
}
