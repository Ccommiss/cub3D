/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 14:35:47 by ccommiss          #+#    #+#             */
/*   Updated: 2020/11/30 14:35:49 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_reverse(char *str)
{
	size_t	n;
	size_t	s;
	size_t	max;
	char	swap;

	n = ft_strlen(str);
	s = 0;
	max = ft_strlen(str) / 2;
	while (n-- > max)
	{
		swap = str[n];
		str[n] = str[s];
		str[s++] = swap;
	}
	return (str);
}
