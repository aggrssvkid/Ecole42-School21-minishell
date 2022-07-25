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

static void	get_cmd(t_evrything *all)
{
	char	tmp;

	tmp = *all->runner;
	*all->runner = '\0';
	all->lgc[all->i].command = ft_strdup(all->start);
	if (all->lgc[all->i].command == 0)
		exit (EXIT_FAILURE);
	*all->runner = tmp;
	all->i++;
	all->runner++;
	all->start = all->runner;
}

int	init_cmds(t_evrything *all)
{
	all->i = 0;
	all->lgc[all->i].command = 0;
	all->start = all->line;
	all->runner = all->start;
	while (*all->runner != '\0')
	{
		if (*all->runner == '|' && check_symbol_not_in_quotes(all->runner) == 1)
			get_cmd(all);
		all->runner++;
	}
	all->lgc[all->i].command = ft_strdup(all->start);
	if (all->lgc[all->i].command == 0)
		return (0);
	return (1);
}