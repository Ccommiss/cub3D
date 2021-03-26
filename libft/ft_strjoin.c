/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 18:47:32 by ccommiss          #+#    #+#             */
/*   Updated: 2021/01/07 08:30:31 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*jointed;
	size_t	size1;
	size_t	size2;

	if (!s1 || !s2)
		return (NULL);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	jointed = (char *)malloc((size1 + size2) * sizeof(char) + 1);
	if (!jointed)
		return (NULL);
	jointed = ft_memcpy(jointed, s1, size1);
	jointed = jointed + size1;
	jointed = ft_memcpy(jointed, s2, size2);
	jointed[size2] = '\0';
	return (jointed - size1);
}
