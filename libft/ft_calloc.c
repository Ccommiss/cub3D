/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 18:45:30 by ccommiss          #+#    #+#             */
/*   Updated: 2020/12/28 11:14:27 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementcount, size_t elementsize)
{
	unsigned char	*ptr;

	ptr = malloc(elementcount * elementsize);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, elementsize * elementcount);
	return (ptr);
}
