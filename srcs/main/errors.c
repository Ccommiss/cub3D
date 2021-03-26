/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:21:51 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/25 13:18:49 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void 	value_errors(t_data *data)
{
	if (data->error == BAD_RGB_VALUES)
		printf("RGB values can't be over 255 or below 0.\n");
	if (data->error == REASSIGNATION)
		printf("Values can't be set up twice.\n");
	if (data->error == HEIGHT_WIDTH_NEG)
		printf("Height and width must be positive values.\n");
	if (data->error == MISSING_INFOS)
		printf("Missing infos.\n");
}

void 	map_errors(t_data *data)
{
	if (data->error == MAP_NOT_CLOSED)
	{
		printf("Map is not closed, or blank was found,");
		printf("or player is not inside the walls.\n");
	}
	if (data->error == NO_PLAYER_FOUND)
		printf("No player found. \n");
	if (data->error == UNEXPECTED_CHAR)
		printf("Unexpected character found in map.\n");
	if (data->error == TWO_PLAYERS)
		printf("Two players found in map.\n");
}

void 	file_errors(t_data *data)
{
	if (data->error == NO_FILE)
		printf("Map must be provided. Usage : ./cub3d [mapname].cub \n");
	if (data->error == BAD_FILENAME)
		printf("Your file must end with '.cub'\n");
	if (data->error == CANNOT_READ_FILE)
		printf("Impossible to read the file. Does it even exist, bro ?\n");
	if (data->error == TOO_MANY_ARGUMENTS)
		printf("Too many arguments.\n");
}

int	error_message(t_data *data, int index)
{
	printf("Error :\n");
	if (data->error == 0)
		data->error = index;
	if (data->error == TEXTURE_NOT_FOUND)
		printf("Texture reference could not be found.\n");
	if (data->error == BAD_RGB_FORMAT)
		printf("Bad RGB color formatting.\n");
	map_errors(data);
	file_errors(data);
	value_errors(data);
	if (data->error == 123)
		printf("Too many arguments.\n");
	close_win(data);
	return (-1);
}
