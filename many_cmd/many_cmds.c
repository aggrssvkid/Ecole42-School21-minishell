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

void	many_cmds(t_evrything *all)
{
	all->pid = malloc(all->n * sizeof(int));
	all->i = 0;
	while (all->i < all->n)
	{
		pipe(all->lgc[all->i].pipex);
		all->i++;
	}
	all->i = 0;
	while (all->i < all->n)
	{
		all->pid[all->i] = fork();
		if (all->pid[all->i] == 0)
			go_execute(all);
		all->i++;
	}
	all->i = 0;
	while (all->i < all->n)
	{
		close(all->lgc[all->i].pipex[0]);
		close(all->lgc[all->i].pipex[1]);
		all->i++;
	}
	all->i = 0;
	while (all->i < all->n)
	{
		waitpid(all->pid[all->i], &g_status, 0);
		g_status = WEXITSTATUS(g_status);
		all->i++;
	}
	free(all->pid);
	all->i = 0;
}