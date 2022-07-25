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

int	check_way_build_func(char *way)
{
	int	x;

	if (access(way, F_OK) == -1)
	{
		ft_putstr_fd("mshell: ", 2);
		ft_putstr_fd(way, 2);
		ft_putstr_fd(": Kogda-nibud ya nachnu trahatsya, no ne segodnya.", 2);
		ft_putstr_fd(" I ti slomaesh moy shell, no ne segodnya.", 2);
		ft_putstr_fd(" (No such file or directory) :(\n", 2);
		return (0);
	}
	x = open(way, O_DIRECTORY);
	if (x != -1)
	{
		close(x);
		ft_putstr_fd("mshell: ", 2);
		ft_putstr_fd(way, 2);
		ft_putstr_fd(": Papka eto, dosvidaniya.\n", 2);
		return (0);
	}
	if (access(way, X_OK) == -1)
	{
		ft_putstr_fd("mshell: ", 2);
		ft_putstr_fd(way, 2);
		ft_putstr_fd(": I CANT EXECUTE THIS FILE, U FICKING MORON!\n", 2);
		return(0);
	}
	return (1);
}

int	check_slash_in_name(char *name)
{
	char *runner;

	runner = name;
	while (*runner != '\0' && *runner != '/')
		runner++;
	if (*runner == '/')
		return (1);
	return (0);
}

int	check_split_symbol(char *symbol)
{
	if (*symbol == '<' && check_symbol_not_in_quotes(symbol) == 1)
		return (1);
	else if (*symbol == '>' && check_symbol_not_in_quotes(symbol) == 1)
		return (1);
	else if (*symbol == '|' && check_symbol_not_in_quotes(symbol) == 1)
		return (1);
	else if (*symbol == '&' && check_symbol_not_in_quotes(symbol) == 1)
		return (1);
	else if (*symbol == ' ' && check_symbol_not_in_quotes(symbol) == 1)
		return (1);
	else if (*symbol == '\0')
		return (1);
	return (0);
}

int	check_symbol_not_in_quotes(char *symbol)
{
	int		double_quotes;
	int		single_quotes;
	char	*runner;

	double_quotes = 0;
	single_quotes = 0;
	runner = symbol + ft_strlen(symbol);
	while (runner != symbol)
	{
		if (*runner == '"' && double_quotes == 0 && single_quotes == 0)
			double_quotes = 1;
		else if (*runner == '\'' && double_quotes == 0 && single_quotes == 0)
			single_quotes = 1;
		else if (*runner == '"' && double_quotes == 1)
			double_quotes = 0;
		else if (*runner == '\'' && single_quotes == 1)
			single_quotes = 0;
		runner--;
	}
	if (*runner == '"' && double_quotes == 1)
		return (1);
	if (*runner == '\'' && single_quotes == 1)
		return (1);
	if (double_quotes == 1 || single_quotes == 1)
		return (0);
	return (1);
}

int	check_logic_and_or(char *str)
{
	if (*str == '|' && *(str + 1) == '|')
	{
		if (check_symbol_not_in_quotes(str) == 1)
			return (1);
	}
	if (*str == '&' && *(str + 1) == '&')
	{
		if (check_symbol_not_in_quotes(str) == 1)
			return (2);
	}
	return (0);
}