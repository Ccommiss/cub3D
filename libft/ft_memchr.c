/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 18:46:31 by ccommiss          #+#    #+#             */
/*   Updated: 2020/11/27 18:46:31 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	tofind;
	unsigned char	*ptr;

	tofind = (unsigned char)c;
	ptr = (unsigned char *)s;
	i = 0;
	while (i < n && ptr[i] != tofind)
		i++;
	if (i < n && ptr[i] == tofind)
		return ((unsigned char *)&s[i]);
	return (NULL);
}
