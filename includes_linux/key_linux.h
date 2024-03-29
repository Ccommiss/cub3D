/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_linux.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 15:21:48 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/26 15:21:49 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_LINUX_H
# define KEY_LINUX_H

# define KEY_W					119
# define KEY_S					115
# define KEY_A					97
# define KEY_D					100
# define KEY_M                  109
# define KEY_J					106
# define KEY_H					104
# define KEY_PLUS               61
# define KEY_MINUS              45
# define KEY_BRACE_R            93
# define KEY_BRACE_L            91
# define KEY_SINGLEQUOT         180
# define KEY_BACKSLASH          92
# define KEY_SPACE				32
# define KEY_PRESS				2
# define KEY_RELEASE			3
# define KEY_SHIFT              65505
# define KEY_RIGHT              65363
# define KEY_LEFT               65361
# define KEY_UP          		65362
# define KEY_DOWN				65364
# define KEY_ESC                65307

# define DESTROY_NOTIFY			33
# define STRUCTURE_NOTIFY_MASK	0
# define ENTER_NOTIFY           7

enum
{
	KEY_PRESS_MASK = (1 << 0),
	KEY_RELEASE_MASK = (1L << 1),
	BUTTON_PRESS_MASK = (1L << 2),
	BUTTON_RELEASE_MASK = (1L << 3),
	ENTER_WINDOW_MASK = (1L << 4)
};

#endif
