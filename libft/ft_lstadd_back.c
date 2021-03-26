/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 18:45:47 by ccommiss          #+#    #+#             */
/*   Updated: 2020/12/28 11:46:40 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*curr;

	if (*alst == NULL)
		*alst = new;
	else
	{
		curr = *alst;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = new;
		curr->next->next = NULL;
	}
}
