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

static int	is_nbr(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	if (*str == '\0')
		return (0);
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str == '\0')
		return (1);
	else
		return (0);
}

void	one_cmd_exec_exit(char **args)
{
	if (args[1] == 0)
	{
		g_status = 0;
		write(1, "exit\n", 5);
		exit(EXIT_SUCCESS);
	}
	if (is_nbr(args[1]) == 0)
	{
		write(1, "exit\n", 5);
		ft_putstr_fd("shell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": numeric arg required\n", 2);
		g_status = 255;
		exit(255);
	}
	else
	{
		if (args[2] != 0)
		{
			ft_putstr_fd("shell: exit: too many args\n", 2);
			g_status = 1;
		}
		else
		{
			write(1, "exit\n", 5);
			g_status = ft_atoi(args[1]);
			exit(ft_atoi(args[1]));
		}
	}
}