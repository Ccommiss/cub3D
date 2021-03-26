/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 18:47:28 by ccommiss          #+#    #+#             */
/*   Updated: 2020/12/28 11:48:46 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new;
	size_t	n;

	n = ft_strlen(s);
	new = (char *)malloc(n * sizeof(char) + 1);
	if (!new)
		return (NULL);
	new = ft_memcpy(new, s, n);
	new[n] = '\0';
	return (new);
}
