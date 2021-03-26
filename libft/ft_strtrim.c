/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 18:48:17 by ccommiss          #+#    #+#             */
/*   Updated: 2020/12/28 11:37:35 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*exception(char **trimmed)
{
	*trimmed = (char *)malloc(1);
	if (!trimmed)
		return (NULL);
	*trimmed[0] = '\0';
	return (*trimmed);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		s;
	int		e;
	int		i;

	if (!s1 || !set)
		return (NULL);
	e = ft_strlen(s1) - 1;
	s = 0;
	i = 0;
	trimmed = NULL;
	while (s <= e && ft_strchr(set, s1[s]) != NULL)
		s++;
	while (e >= 0 && ft_strrchr(set, s1[e]) != NULL)
		e--;
	if (s1[0] == '\0' || (s > e))
		return (exception(&trimmed));
	trimmed = (char *)malloc((e - s + 2) * sizeof(char));
	if (!trimmed)
		return (NULL);
	while (s <= e)
		trimmed[i++] = s1[s++];
	trimmed[i] = '\0';
	return (trimmed);
}
