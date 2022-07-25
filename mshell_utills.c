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

void	signals_go(t_evrything *all)
{
	all->history_list = 0;
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	free_heredocs(t_evrything *all)
{
	if (all->heredoc_nbr != 0)
	{
		all->i = 0;
		while (all->heredoc_names[all->i] != 0)
		{
			unlink(all->heredoc_names[all->i]);
			free(all->heredoc_names[all->i]);
			all->i++;
		}
		free(all->heredoc_names);
	}
}

void	free_inited_params(t_evrything *all)
{
	all->i = 0;
	while (all->i < all->n)
	{
		free(all->lgc[all->i].cmd_args);
		free(all->lgc[all->i].command);
		all->i++;
	}
	free(all->line);
	free(all->lgc);
}

void	move_str_pointer(t_evrything *all)
{
	if (*all->end == '\0')
		all->str = all->end;
	else if (g_status == 0 && *all->end == '&')
		all->str = all->end + 2;
	else if (g_status != 0 && *all->end == '|')
		all->str = all->end + 2;
	else if (g_status == 0 && *all->end == '|')
	{
		all->str = all->end;
		while (*all->str != '\0' && check_logic_and_or(all->str) != 2)
			all->str++;
		if (*all->str != '\0')
			all->str = all->str + 2;
	}
	else if (g_status != 0 && *all->end == '&')
	{
		all->str = all->end;
		while (*all->str != '\0' && check_logic_and_or(all->str) != 1)
			all->str++;
		if (*all->str != '\0')
			all->str = all->str + 2;
	}
}

void	init_left_right_pipes_fd(t_evrything *all)
{
	all->i = 0;
	while (all->i < all->n)
	{
		if (all->i == 0)
			all->lgc[all->i].left_pipe = 0;
		else
			all->lgc[all->i].left_pipe = 1;
		if (all->i == all->n - 1)
			all->lgc[all->i].right_pipe = 0;
		else
			all->lgc[all->i].right_pipe = 1;
		all->lgc[all->i].fd_out = 1;
		all->lgc[all->i].fd_in = 0;
		all->i++;
	}
}