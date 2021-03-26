/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 21:24:02 by ccommiss          #+#    #+#             */
/*   Updated: 2021/03/26 10:15:07 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_F 3
# define KEY_H 4
# define KEY_G 5
# define KEY_Z 6
# define KEY_X 7
# define KEY_C 8
# define KEY_V 9
# define KEY_B 11
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15
# define KEY_Y 16
# define KEY_T 17
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_THREE 20
# define KEY_FOUR 21
# define KEY_SIX 22
# define KEY_FIVE 23
# define KEY_NINE 25
# define KEY_SEVEN 26
# define KEY_EIGHT 28
# define KEY_ZERO 29
# define KEY_BRACE_R 30
# define KEY_O 31
# define KEY_U 32
# define KEY_BRACE_L 33
# define KEY_I 34
# define KEY_P 35
# define KEY_L 37
# define KEY_J 38
# define KEY_K 40
# define KEY_SEMI 41
# define KEY_N 45
# define KEY_M 46
# define KEY_TAB 48
# define KEY_SPACE 49
# define KEY_ESC 53
# define KEY_SINGLEQUOT 39
# define KEY_BACKSLASH 42
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_SHIFT 257

/*
** EVENTS
*/
# define KEY_PRESS				2
# define KEY_RELEASE			3
# define BUTTON_PRESS			4
# define BUTTON_RELEASE			5
# define MOTION_NOTIFY			6
# define DESTROY_NOTIFY			17
# define ENTER_NOTIFY           7

/*
** EVENT MASKS
*/

//# define KEY_PRESS_MASK			(1L << 0)
// # define KEY_RELEASE_MASK		(1L << 1)
// # define BUTTON_PRESS_MASK		(1L << 2)
// # define BUTTON_RELEASE_MASK	(1L << 3)
// # define POINTER_MOTION_MASK	(1L << 6)
// # define BUTTON1_MOTION_MASK	(1L << 8)
// # define BUTTON2_MOTION_MASK	(1L << 9)
// # define BUTTON3_MOTION_MASK	(1L << 10)
// # define BUTTON4_MOTION_MASK	(1L << 11)
// # define BUTTON5_MOTION_MASK	(1L << 12)
// # define STRUCTURE_NOTIFY_MASK	(1L << 17)
// # define ENTER_WINDOW_MASK      (1L << 4)

enum
{
	KEY_PRESS_MASK	= (1 << 0),
	KEY_RELEASE_MASK = (1L << 1),
	BUTTON_PRESS_MASK =	(1L << 2),
	BUTTON_RELEASE_MASK = (1L << 3),
	STRUCTURE_NOTIFY_MASK = (1L << 17),
	ENTER_WINDOW_MASK = (1L << 4)
};




#endif
