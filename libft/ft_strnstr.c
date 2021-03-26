/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 18:48:08 by ccommiss          #+#    #+#             */
/*   Updated: 2021/01/08 17:36:05 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_mystrncmp(const char *first, const char *second, size_t length)
{
	size_t	i;

	i = 0;
	if ((first[0] == '\0' && second[0] == '\0') || length == 0)
		return (0);
	while (first[i] && second[i] && i < length - 1)
		i++;
	return ((unsigned char)first[i] - (unsigned char)second[i]);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	lit_size;

	i = 0;
	lit_size = ft_strlen(little);
	if (*little == '\0')
		return ((char *)big);
	while (i < len && big[i])
	{
		while (big[i] != little[0] && big[i])
			i++;
		if (i + lit_size <= len
			&& ft_mystrncmp((big + i), little, lit_size) == 0)
			return ((char *)big + i);
		else if (big[i])
			i++;
	}
	return (NULL);
}
