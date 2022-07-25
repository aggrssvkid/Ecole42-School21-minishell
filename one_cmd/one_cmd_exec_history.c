/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:45:33 by anemesis          #+#    #+#             */
/*   Updated: 2022/06/01 15:58:50 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft/libft.h"

static void	print_history(t_hist *history_list, int nbr)
{
	t_hist	*runner;
	int		i;
	char	*chislo;

	if (nbr == 0)
		return ;
	i = 1;
	runner = history_list;
	while (runner->next != 0)
		runner = runner->next;
	while (runner->prev != 0 && i < nbr)
	{
		runner = runner->prev;
		i++;
	}
	while (runner!= 0)
	{
		chislo = ft_itoa(runner->cmd_num);
		printf("   %s   %s\n", chislo, runner->cmd);
		free(chislo);
		runner = runner->next;
	}
}

static int	it_is_num(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	if (*str == '\0')
		return (0);
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str != '\0')
		return (0);
	return (1);
}

static int	check_allright(char **args)
{
	if (it_is_num(args[1]) == 0)
	{
		ft_putstr_fd("shell: history: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric arg...bla bla, nu hernu ne vvodi,korohe\n", 2);
		g_status = 1;
		return (0);
	}
	if (*args[1] == '-')
	{
		ft_putstr_fd("mshell: usage: history: nu tipa bez opciy\n", 2);
		g_status = 2;
		return (0);
	}
	if (args[2] != 0)
	{
		ft_putstr_fd("mshell: history: too many args, zaebal! >:(\n", 2);
		g_status = 1;
		return (0);
	}
	return (1);
}

int	one_cmd_exec_history(t_hist *history_list, char **args)
{
	int		x;
	char	*str;

	if (history_list == 0)
		return (0);
	if (args[1] == 0)
	{
		print_history(history_list, 1000000);
		g_status = 0;
		return (1);
	}
	if (check_allright(args) == 0)
		return (0);
	str = args[1];
	x = 1;
	if (args[1][0] == '0')
	{
		while (*str == '0')
			str++;
		if (*str == '\0')
			x = 0;
		print_history(history_list, x);
		g_status = 0;
		return (1);
	}
	x = ft_atoi(str);
	if (x == 0 || x == -1)
	{
		ft_putstr_fd("shell: history: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric arg...bla bla, nu hernu ne vvodi,koroce\n", 2);
		g_status = 1;
		return (0);
	}
	print_history(history_list, x);
	g_status = 0;
	return (1);
}
