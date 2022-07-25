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

void	use_pipe(t_evrything *all)
{
	int	k;

	if (all->lgc[all->i].fd_in != 0)
		dup2(all->lgc[all->i].fd_in, 0);
	else if (all->lgc[all->i].left_pipe == 1)
		dup2(all->lgc[all->i - 1].pipex[0], 0);
	if (all->lgc[all->i].fd_out != 1)
		dup2(all->lgc[all->i].fd_out, 1);
	else if(all->lgc[all->i].right_pipe == 1)
		dup2(all->lgc[all->i].pipex[1], 1);
	k = 0;
	while (k < all->n)
	{
		if (k != all->i)
			close(all->lgc[k].pipex[1]);
		k++;
	}
	k = 0;
	while (k < all->n)
	{
		if (k != all->i - 1)
			close(all->lgc[k].pipex[0]);
		k++;
	}
}

static void	parse_cmd(t_evrything *all)
{
	int	checker;

	all->lgc[all->i].command = parse_dollar(all->lgc[all->i].command, all->our_env);
	if (all->lgc[all->i].command == 0)
		exit(1);
	checker = check_rdrct_files(all->lgc[all->i].command, &(all->lgc[all->i].fd_out), &(all->lgc[all->i].fd_in), all->n);
	if (checker == 0)
		exit(1);
	all->lgc[all->i].cmd_args->prog_name = init_prog_name(all->lgc[all->i].command);
	if (all->lgc[all->i].cmd_args->prog_name == 0)
		exit(0);
	if (*all->lgc[all->i].cmd_args->prog_name == '\0')
	{
		ft_putstr_fd("mshell: NU VVEDI TI ADEKVATNUYU KOMANDU,CHUCHELO!\n", 2);
		exit(127);
	}
	all->lgc[all->i].prog_build = check_build_func(all->lgc[all->i].cmd_args->prog_name);
	if (all->lgc[all->i].prog_build == 1)
	{
		if (check_slash_in_name(all->lgc[all->i].cmd_args->prog_name) == 1)
		{
			if (check_way_build_func(all->lgc[all->i].cmd_args->prog_name) == 0)
				exit (127);
		}
		all->lgc[all->i].cmd_args->prog_way = ft_strdup(all->lgc[all->i].cmd_args->prog_name);
	}
	else
		all->lgc[all->i].cmd_args->prog_way = init_prog_way(all->lgc[all->i].cmd_args->prog_name, all->our_env.head);
	all->lgc[all->i].cmd_args->prog_args = init_prog_args(all->lgc[all->i].command);
}

void	go_execute(t_evrything *all)
{
	parse_cmd(all);
	use_pipe(all);
	if (all->lgc[all->i].prog_build == 1)
		many_cmd_exec_our_func(all);
	else
		execve(all->lgc[all->i].cmd_args->prog_way, all->lgc[all->i].cmd_args->prog_args, list_to_array(&(all->our_env)));
}