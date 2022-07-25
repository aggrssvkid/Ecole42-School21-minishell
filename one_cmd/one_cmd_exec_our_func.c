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

static void	one_cmd_exec(char *name, t_evrything *all)
{
	int		p;
	int		ret;

	if(ft_strcmp(name, "history") == EQUAL)
	{
		if (all->lgc[0].fd_out != 1)
		{
			p = fork();
			if (p == 0)
			{
				if (all->lgc[0].fd_out != 1)
					dup2(all->lgc[0].fd_out, 1);
				if (all->lgc[0].fd_in != 0)
					dup2(all->lgc[0].fd_out, 0);
				ret = one_cmd_exec_history(all->history_list, all->lgc[0].cmd_args->prog_args);
				if (ret == 0)
					exit(1);
				exit(0);
			}
			else
				wait(&g_status);
		}
		else
			one_cmd_exec_history(all->history_list, all->lgc[0].cmd_args->prog_args);
	}
	else if (ft_strcmp(name, "echo") == EQUAL)
	{
		if (all->lgc[0].fd_out != 1)
		{
			p = fork();
			if (p == 0)
			{
				if (all->lgc[0].fd_out != 1)
					dup2(all->lgc[0].fd_out, 1);
				if (all->lgc[0].fd_in != 0)
					dup2(all->lgc[0].fd_out, 0);
				one_cmd_exec_echo(all->lgc[0].cmd_args->prog_args);
				exit(0);
			}
			else
				wait(&g_status);
		}
		else
			one_cmd_exec_echo(all->lgc[0].cmd_args->prog_args);
	}
	else if (ft_strcmp(name, "cd") == EQUAL)
		one_cmd_exec_cd(all->lgc[0].cmd_args->prog_args, &(all->our_env));
	else if (ft_strcmp(name, "pwd") == EQUAL)
	{
		if (all->lgc[0].fd_out != 1)
		{
			p = fork();
			if (p == 0)
			{
				if (all->lgc[0].fd_out != 1)
					dup2(all->lgc[0].fd_out, 1);
				if (all->lgc[0].fd_in != 0)
					dup2(all->lgc[0].fd_out, 0);
				one_cmd_exec_pwd();
				exit(0);
			}
			else
				wait(&g_status);
		}
		else
			one_cmd_exec_pwd();
	}
	else if (ft_strcmp(name, "export") == EQUAL)
		one_cmd_exec_export(all->lgc[0].cmd_args->prog_args,  &(all->our_env));
	else if (ft_strcmp(name, "unset") == EQUAL)
		one_cmd_exec_unset(all->lgc[0].cmd_args->prog_args,  &(all->our_env));
	else if (ft_strcmp(name, "env") == EQUAL)
	{
		if (all->lgc[0].fd_out != 1)
		{
			p = fork();
			if (p == 0)
			{
				if (all->lgc[0].fd_out != 1)
					dup2(all->lgc[0].fd_out, 1);
				if (all->lgc[0].fd_in != 0)
					dup2(all->lgc[0].fd_out, 0);
				ret = one_cmd_exec_env(all->lgc[0].cmd_args->prog_args,  &(all->our_env));
				if (ret == 0)
					exit(1);
				else
					exit(0);
			}
			else
				wait(&g_status);
		}
		else
			one_cmd_exec_env(all->lgc[0].cmd_args->prog_args,  &(all->our_env));
	}
	else if (ft_strcmp(name, "exit") == EQUAL)
		one_cmd_exec_exit(all->lgc[0].cmd_args->prog_args);
}

void	one_cmd_exec_our_func(t_evrything *all)
{
	char	*runner;

	runner = all->lgc[0].cmd_args->prog_args[0];
	while (*runner != '\0' && *runner != '/')
		runner++;
	if (*runner == '/')
	{
		runner = all->lgc[0].cmd_args->prog_args[0] + ft_strlen(all->lgc[0].cmd_args->prog_args[0]);
		while (*runner != '/')
			runner--;
		runner++;
		one_cmd_exec(runner, all);
	}
	else
		one_cmd_exec(all->lgc[0].cmd_args->prog_args[0], all);
}