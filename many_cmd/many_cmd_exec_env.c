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

static int	check_env_errors(char **args, t_env *env_list)
{
	if (ft_strcmp(args[1], "PWD") == EQUAL \
		|| ft_strcmp(args[1], "LOGNAME") == EQUAL)
	{
		if (args[2] == 0)
		{
			printf("%s\n", getenv(args[1]));
			exit(0);
		}
		else
		{
			if (ft_strcmp(args[1], "PWD") == EQUAL)
				ft_putstr_fd("usage: pwd [-L | -P]\n", 2);
			else if (ft_strcmp(args[1], "LOGNAME") == EQUAL)
				ft_putstr_fd("usage: logname\n", 2);
			exit(1);
		}
	}
	else if (args[1][0] == '=')
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": Invalid argument\n", 2);
		exit(1);
	}
	else if (ft_strchr(args[1], '=') == NULL)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
	}
	else
		many_cmd_exec_export(args, env_list);
	return (0);
}

int	many_cmd_exec_env(char **args, t_env *env_list)
{
	t_node	*tmp_node;

	if (args[1] != NULL && check_env_errors(args, env_list) == 1)
		exit(1);
	tmp_node = env_list->head;
	while (tmp_node)
	{
		printf("%s=%s\n", tmp_node->key, tmp_node->value);
		tmp_node = tmp_node->next;
	}
	return (1);
	exit(0);
}