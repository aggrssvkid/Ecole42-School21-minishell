/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:38:57 by anemesis          #+#    #+#             */
/*   Updated: 2022/05/30 17:08:55 by anemesis         ###   ########.fr       */
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
			g_status = 0;
			return (1);
		}
		else
		{
			if (ft_strcmp(args[1], "PWD") == EQUAL)
				ft_putstr_fd("usage: pwd [-L | -P]\n", 2);
			else if (ft_strcmp(args[1], "LOGNAME") == EQUAL)
				ft_putstr_fd("usage: logname\n", 2);
			g_status = 1;
			return (1);
		}
	}
	else if (args[1][0] == '=')
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": Invalid argument\n", 2);
		g_status = 1;
		return (1);
	}
	else if (ft_strchr(args[1], '=') == NULL)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_status = 127;
		return (1);
	}
	else
		one_cmd_exec_export(args, env_list);
	return (0);
}

int	one_cmd_exec_env(char **args, t_env *env_list)
{
	t_node	*tmp_node;

	if (args[1] != NULL && check_env_errors(args, env_list) == 1)
		return (0);
	tmp_node = env_list->head;
	while (tmp_node)
	{
		printf("%s=%s\n", tmp_node->key, tmp_node->value);
		tmp_node = tmp_node->next;
	}
	g_status = 0;
	return (1);
}
