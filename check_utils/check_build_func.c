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

static int	check_strcmp(char *prog_name)
{
	if (ft_strcmp(prog_name, "echo") == 0)
		return (1);
	else if (ft_strcmp(prog_name, "pwd") == 0)
		return (1);
	else if (ft_strcmp(prog_name, "cd") == 0)
		return (1);
	else if (ft_strcmp(prog_name, "unset") == 0)
		return (1);
	else if (ft_strcmp(prog_name, "export") == 0)
		return (1);
	else if (ft_strcmp(prog_name, "env") == 0)
		return (1);
	else if (ft_strcmp(prog_name, "exit") == 0)
		return (1);
	else if (ft_strcmp(prog_name, "history") == 0)
		return (1);
	return (0);
}

static int	check_last_word(char *prog_name)
{
	char	*runner;

	runner = prog_name + ft_strlen(prog_name);
	while (*runner != '/')
		runner--;
	runner++;
	if (ft_strcmp(runner, "echo") == 0)
		return (1);
	else if (ft_strcmp(runner, "pwd") == 0)
		return (1);
	else if (ft_strcmp(runner, "cd") == 0)
		return (1);
	else if (ft_strcmp(runner, "unset") == 0)
		return (1);
	else if (ft_strcmp(runner, "export") == 0)
		return (1);
	else if (ft_strcmp(runner, "env") == 0)
		return (1);
	else if (ft_strcmp(runner, "exit") == 0)
		return (1);
	else if (ft_strcmp(runner, "history") == 0)
		return (1);
	return (0);
}

int	check_build_func(char *prog_name)
{
	char	*runner;

	runner = prog_name;
	while (*runner != '\0')
	{
		if (*runner == '/')
			return (check_last_word(prog_name));
		runner++;
	}
	return (check_strcmp(prog_name));
}
