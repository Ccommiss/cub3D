/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 18:45:59 by ccommiss          #+#    #+#             */
/*   Updated: 2020/12/28 11:46:54 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	**init;
	t_list	*tmp;

	init = lst;
	while ((*lst) != NULL)
	{
		del((*lst)->content);
		tmp = *lst;
		(*lst) = (*lst)->next;
		free(tmp);
	}
	free(*lst);
	init = NULL;
}
