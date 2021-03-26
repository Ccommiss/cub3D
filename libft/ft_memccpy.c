/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 18:46:27 by ccommiss          #+#    #+#             */
/*   Updated: 2020/11/27 18:46:27 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*dst;
	unsigned char	*srce;
	unsigned char	tofind;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	dst = (unsigned char *)dest;
	srce = (unsigned char *)src;
	tofind = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		dst[i] = srce[i];
		if (srce[i] == tofind)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
