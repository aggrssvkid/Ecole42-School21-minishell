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

static char	**join_name_path(char **ways, char *prog_name)
{
	char	*helper;
	int		i;

	i = 0;
	while (ways[i] != 0)
	{
		helper = ways[i];
		ways[i] = ft_strjoin(ways[i], "/");
		free(helper);
		helper = ways[i];
		ways[i] = ft_strjoin(ways[i], prog_name);
		free(helper);
		i++;
	}
	return (ways);
}

static void	check_path_way(char **ways, int i, char *prog_name)
{
	if (ways[i] == 0)
	{
		ft_putstr_fd("mshell: ", 2);
		ft_putstr_fd(prog_name, 2);
		ft_putstr_fd(": COMMAND NOT NASHLI! GL HF :(\n", 2);
		exit(127);
	}
	if (open(ways[i], O_DIRECTORY) != -1)
	{
		ft_putstr_fd("mshell: ", 2);
		ft_putstr_fd(ways[i], 2);
		ft_putstr_fd(": ETO PAPKA!\n", 2);
		exit(126);
	}
	if (access(ways[i], X_OK) != 0)
	{
		ft_putstr_fd("mshell: ", 2);
		ft_putstr_fd(ways[i], 2);
		ft_putstr_fd(": CANT EXECUTE THIS SHIT!\n", 2);
		exit(126);
	}
}

static void	check_right_way(char *prog_way)
{
	if (access(prog_way, F_OK) == -1)
	{
		ft_putstr_fd("mshell: ", 2);
		ft_putstr_fd(prog_way, 2);
		ft_putstr_fd(": NO SUCK FILE OR DIRECTORY, vsego dobrogo!\n", 2);
		exit(127);
	}
	if (open(prog_way, O_DIRECTORY) != -1)
	{
		ft_putstr_fd("mshell: ", 2);
		ft_putstr_fd(prog_way, 2);
		ft_putstr_fd(": ZDAROVA OTEC (papka)!\n", 2);
		exit(126);
	}
	if (access(prog_way, X_OK) == -1)
	{
		ft_putstr_fd("mshell: ", 2);
		ft_putstr_fd(prog_way, 2);
		ft_putstr_fd(": I CANT EXECUTE THIS FILE, U FICKING MORON!\n", 2);
		exit(126);
	}
}

char	*find_path_way(char *prog_name, t_node *head)
{
	t_node	*runner;
	char	**ways;
	char	*prog_way;
	int		i;

	runner = head;
	while (runner != 0 && ft_strcmp("PATH", runner->key) != 0)
		runner = runner->next;
	if (runner == 0)
	{
		ft_putstr_fd("mshell: ", 2);
		ft_putstr_fd(prog_name, 2);
		ft_putstr_fd(": NO SUCH FILE OR DIRECTORA NET\n", 2);
		exit(127);
	}
	ways = ft_split(runner->value, ':');
	ways = join_name_path(ways, prog_name);
	i = 0;
	while (ways[i] != 0 && access(ways[i], F_OK) != 0)
		i++;
	check_path_way(ways, i, prog_name);
	prog_way = ft_strdup(ways[i]);
	return (prog_way);
}

char	*init_prog_way(char *prog_name, t_node *head)
{
	char	*runner;
	char	*prog_way;

	runner = prog_name;
	prog_way = 0;
	while (*runner != '\0')
	{
		if (*runner == '/')
		{
			check_right_way(prog_name);
			prog_way = ft_strdup(prog_name);
			return (prog_way);
		}
		runner++;
	}
	prog_way = find_path_way(prog_name, head);
	return (prog_way);
}
