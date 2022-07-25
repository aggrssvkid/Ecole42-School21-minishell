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

static int	check_flag_n(char *str)
{
	if (str == 0)
		return (0);
	if (*str != '-')
		return (0);
	else
		str++;
	if (*str == '\0')
		return (0);
	while (*str != '\0')
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

void	many_cmd_exec_echo(char **args)
{
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	if (args[1] == 0)
	{
		write(1, "\n", 1);
		exit(0);
	}
	flag = check_flag_n(args[i]);
	while (check_flag_n(args[i]) == 1)
		i++;
	while (args[i] != 0)
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1] != 0)
			write(1, " ", 1);
		i++;
	}
	if (flag != 1)
		write(1, "\n", 1);
	exit(0);
}
