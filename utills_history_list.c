/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoye <enoye@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 14:20:44 by enoye             #+#    #+#             */
/*   Updated: 2022/04/24 14:20:52 by enoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft/libft.h"

t_hist	*add_new_history_list(t_hist *begin, char *str_input)
{
	t_hist	*end;

	if (begin == 0)
	{
		begin = new_history_list(str_input);
		begin->prev = 0;
		begin->cmd_num = 1;
		return (begin);
	}
	end = begin;
	while (end->next != 0)
		end = end->next;
	end->next = new_history_list(str_input);
	end->next->prev = end;
	end = end->next;
	end->cmd_num = end->prev->cmd_num + 1;
	return (begin);
}

t_hist	*new_history_list(char *str_input)
{
	t_hist	*var;

	var = malloc(sizeof(t_hist));
	var->cmd = ft_strdup(str_input);
	var->next = 0;
	return (var);
}