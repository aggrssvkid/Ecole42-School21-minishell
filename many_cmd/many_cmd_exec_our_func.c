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

static void	many_cmd_exec(char *name, t_evrything *all)
{
	if (ft_strcmp(name, "echo") == EQUAL)
		many_cmd_exec_echo(all->lgc[all->i].cmd_args->prog_args);
	else if (ft_strcmp(name, "cd") == EQUAL)
		many_cmd_exec_cd(all->lgc[all->i].cmd_args->prog_args, &(all->our_env));
	else if (ft_strcmp(name, "env") == EQUAL)
		many_cmd_exec_env(all->lgc[all->i].cmd_args->prog_args, &(all->our_env));
	else if (ft_strcmp(name, "exit") == EQUAL)
		many_cmd_exec_exit(all->lgc[all->i].cmd_args->prog_args);
	else if (ft_strcmp(name, "export") == EQUAL)
		many_cmd_exec_export(all->lgc[all->i].cmd_args->prog_args, &(all->our_env));
	else if (ft_strcmp(name, "unset") == EQUAL)
		many_cmd_exec_unset(all->lgc[all->i].cmd_args->prog_args, &(all->our_env));
	else if (ft_strcmp(name, "pwd") == EQUAL)
		many_cmd_exec_pwd();
	else if (ft_strcmp(name, "history") == EQUAL)
		many_cmd_exec_history(all->history_list ,all->lgc[all->i].cmd_args->prog_args);
}

void	many_cmd_exec_our_func(t_evrything *all)
{
	char	*runner;

	runner = all->lgc[all->i].cmd_args->prog_args[0];
	while (*runner != '\0' && *runner != '/')
		runner++;
	if (*runner == '/')
	{
		runner = all->lgc[all->i].cmd_args->prog_args[0] + ft_strlen(all->lgc[all->i].cmd_args->prog_args[0]);
		while (*runner != '/')
			runner--;
		runner++;
		many_cmd_exec(runner, all);
	}
	else
		many_cmd_exec(all->lgc[all->i].cmd_args->prog_args[0], all);
}