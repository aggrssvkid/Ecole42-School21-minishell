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

static void	init_line_lgc_args(t_evrything *all)
{
	all->runner = all->start;
	all->i = 0;
	all->tmp = *all->end;
	*all->end = '\0';
	all->line = ft_strdup(all->str);
	init_cmds(all);
	*all->end = all->tmp;
	all->i = 0;
	while (all->i < all->n)
	{
		all->lgc[all->i].cmd_args = malloc(sizeof(t_prog));
		if (all->lgc[all->i].cmd_args == 0)
			exit(0);
		all->i++;
	}
	init_left_right_pipes_fd(all);
}

static void	get_ncmds_and_end_line(t_evrything *all)
{
	all->runner = all->str;
	while (*all->runner != '\0' &&  check_logic_and_or(all->runner) == 0)
		all->runner++;
	all->end = all->runner;
	all->start = all->str;
	all->runner = all->start;
	all->n = 1;
	while (all->runner != all->end)
	{
		if (*all->runner == '|' && check_symbol_not_in_quotes(all->runner) == 1)
			all->n++;
		all->runner++;
	}
	all->lgc = malloc(all->n * sizeof(t_logic));
	if (all->lgc == 0)
		exit(EXIT_FAILURE);
}

static void	syntax_heredoc_history(t_evrything *all)
{
	if (all->str == 0)
	{
		ft_putstr_fd("mshell exit\n", 1);
		exit(0);
	}
	all->history_list = add_new_history_list(all->history_list, all->str);
	while (syntax_are_you_good(all->str) == 0)
	{
		g_status = 258;
		free(all->str);
		all->str = readline("mshell: poprobuy slomat, clown> ");
		if (all->str == 0)
		{
			ft_putstr_fd("mshell exit\n", 1);
			exit(0);
		}
		all->history_list = add_new_history_list(all->history_list, all->str);
	}
	all->heredoc_nbr = heredoc_diff_nbr(all->str);
	if (all->heredoc_nbr != 0)
	{
		all->heredoc_names = heredoc_get_names(all->heredoc_nbr);
		heredoc_fucking(all);
	}
	all->input_str = all->str;
}

int	main(int argc, char **argv, char **env)
{
	(void)	argc;
	(void)	argv;
	t_evrything	all;

	all.our_env = copy_env(env);
	env_update_params(&(all.our_env));
	signals_go(&all);
	while(1)
	{
		all.str = readline("mshell: poprobuy slomat, clown> ");
		add_history(all.str);
		syntax_heredoc_history(&all);
		while (*all.str != '\0')
		{
			get_ncmds_and_end_line(&all);
			init_line_lgc_args(&all);
			if (all.n == 1)
				one_cmd(&all);
			else
				many_cmds(&all);
			move_str_pointer(&all);
			free_inited_params(&all);
		}
		free(all.input_str);
		free_heredocs(&all);
	}
}