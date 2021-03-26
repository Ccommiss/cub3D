/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 18:45:16 by ccommiss          #+#    #+#             */
/*   Updated: 2020/12/28 11:19:11 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	nbr;
	int	neg;

	nbr = 0;
	neg = 0;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\r' || *nptr == '\v'
		|| *nptr == '\f' || *nptr == '\n')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			neg = 1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		nbr = nbr * 10;
		nbr = nbr + (*nptr - 48);
		nptr++;
	}
	if (neg == 1)
		nbr = nbr * -1;
	return (nbr);
}
