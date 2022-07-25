/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:47:41 by anemesis          #+#    #+#             */
/*   Updated: 2022/05/30 16:12:12 by anemesis         ###   ########.fr       */
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

void	one_cmd_exec_echo(char **args)
{
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	g_status = 0;
	if (args[1] == 0)
	{
		write(1, "\n", 1);
		return ;
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
}
