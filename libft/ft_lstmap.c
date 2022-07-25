/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:18:35 by enoye             #+#    #+#             */
/*   Updated: 2021/11/18 18:18:39 by enoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	**iter;
	t_list	*new;

	if (lst == 0)
		return (0);
	new = ft_lstnew(lst -> content);
	if (new == 0)
		return (0);
	new -> content = (*f)(lst -> content);
	iter = &new;
	lst = lst -> next;
	while (lst != 0)
	{
		new = ft_lstnew(lst -> content);
		if (new == 0)
		{
			ft_lstclear(iter, del);
			return (0);
		}
		new -> content = (*f)(lst -> content);
		ft_lstadd_back(iter, new);
		lst = lst -> next;
	}
	return (*iter);
}
