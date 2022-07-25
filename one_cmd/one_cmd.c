/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:33:17 by enoye             #+#    #+#             */
/*   Updated: 2021/11/08 22:21:54 by enoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft/libft.h"

static void	go_one_cmd(t_evrything *all)
{
	int	p;

	all->i = 0;
	all->lgc[0].cmd_args->prog_name = init_prog_name(all->lgc[0].command);
	if (all->lgc[0].cmd_args->prog_name == 0)
	{
		g_status = 0;
		return ;
	}
	if (*all->lgc[0].cmd_args->prog_name == '\0')
	{
		ft_putstr_fd("mshell: ", 2);
		ft_putstr_fd("NU KONECHNO MI NE NAYDEM KOMANDU BEZ IMENI, DURIK\n", 2);
		g_status = 1;
		free(all->lgc[0].cmd_args->prog_name);
		return ;
	}
	all->lgc[0].prog_build = check_build_func(all->lgc[0].cmd_args->prog_name);
	if (all->lgc[0].prog_build == 1)
	{
		if (check_slash_in_name(all->lgc[0].cmd_args->prog_name) == 1)
		{
			if (check_way_build_func(all->lgc[0].cmd_args->prog_name) == 0)
			{
				g_status = 127;
				return ;
			}
		}
		all->lgc[0].cmd_args->prog_args = init_prog_args(all->lgc[0].command);
		all->lgc[0].cmd_args->prog_way = ft_strdup(all->lgc[0].cmd_args->prog_name);
		one_cmd_exec_our_func(all);
		free(all->lgc[0].cmd_args->prog_name);
		del_matrix(all->lgc[0].cmd_args->prog_args);
		free(all->lgc[0].cmd_args->prog_way);
	}
	else
	{
		p = fork();
		if (p == 0)
		{
			if (all->lgc[0].fd_out != 1)
				dup2(all->lgc[0].fd_out, 1);
			if (all->lgc[0].fd_in != 0)
				dup2(all->lgc[0].fd_in, 0);
			all->lgc[0].cmd_args->prog_args = init_prog_args(all->lgc[0].command);
			all->lgc[0].cmd_args->prog_way = init_prog_way(all->lgc[0].cmd_args->prog_name, all->our_env.head);
			execve(all->lgc[0].cmd_args->prog_way, all->lgc[0].cmd_args->prog_args, list_to_array(&(all->our_env)));
		}
		else
		{
			wait(&g_status);
			g_status = WEXITSTATUS(g_status);
		}
		free(all->lgc[0].cmd_args->prog_name);
	}	
}

void	one_cmd(t_evrything *all)
{
	all->lgc[0].command = parse_dollar(all->lgc[0].command, all->our_env);
	if (all->lgc[0].command == 0)
	{
		g_status = 1;
		return ;
	}
	all->i = check_rdrct_files(all->lgc[0].command, &(all->lgc[0].fd_out), &(all->lgc[0].fd_in), all->n);
	if (all->i == 0)
	{
		g_status = 1;
	}
	else
		go_one_cmd(all);
	if (all->lgc[0].fd_out != 1 && all->lgc[0].fd_out != 0)
		close(all->lgc[0].fd_out);
	all->lgc[0].fd_out = 1;
	if (all->lgc[0].fd_in != 0)
		close(all->lgc[0].fd_in);
	all->lgc[0].fd_in = 0;
}