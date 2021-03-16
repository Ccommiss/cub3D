/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:18:00 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/15 12:40:03 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data		data;
	t_display	info;
	int			fd;

	(void)argc;
	fd = open(argv[1], O_RDONLY);
	int test = read(fd, 0, 0);
	if (test < 0)
	{
		printf("Bad argument.\n");
		return (-1);
	}
	data.info = &info;
	init_base(&data);
	ft_parse(fd, &data);
	printf ("AFTER FT_PARSE\n");
	init_struct(&data);
	printf ("AFTER INIT STRUCT\n");
	if (argc == 3 && ft_strncmp(argv[2], "--save", 7) == 0)
	{
		printf ("SAVE TO BMP \n");
		save_bmp(&data);
		return (1);
	}
	display(&data);
	mlx_hook(data.win, KEY_PRESS, 1L << 0, key_hook, &data);
	mlx_hook(data.win, KEY_RELEASE, 1L << 0, speed_hook, &data); //retour normal
	//mlx_hook(data.win, 17, (1L << 17), close_win, &data);
	mlx_hook(data.win, 33, 0, close_win, &data); // linux
	mlx_loop(data.mlx);

}