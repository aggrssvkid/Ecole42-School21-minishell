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

static char	*if_or_and_pipe(char *runner)
{
	if (*runner == '|' && *(runner + 1) != '|')
	{
		runner = syntax_pipe(runner);
		if (runner == 0)
			return (0);
	}
	else if (*runner == '|' && *(runner + 1) == '|')
	{
		runner = syntax_logic_or(runner);
		if (runner == 0)
			return (0);
	}
	else if (*runner == '&')
	{
		runner = syntax_logic_and(runner);
		if (runner == 0)
			return (0);
	}
	return (runner);
}

static char	*if_rdrct_quotes(char *runner)
{
	if (*runner == '"' || *runner == '\'')
	{
		runner = syntax_quotes(runner);
		if (runner == 0)
			return (0);
	}
	else if (*runner == '<')
	{
		runner = syntax_left_rdrct(runner);
		if (runner == 0)
			return (0);
	}
	else if (*runner == '>')
	{
		runner = syntax_right_rdrct(runner);
		if (runner == 0)
			return (0);
	}
	return (runner);
}

int	syntax_are_you_good(char *line)
{
	char	*runner;
	char	*save;

	runner = line;
	while (*runner == ' ')
		runner++;
	if (*runner == '|' || *runner == '&')
	{
		ft_putstr_fd("mshell: syntax error: davay zanovo drujochek\n", 2);
		return (0);
	}
	while (*runner != '\0')
	{
		while (*runner == ' ')
			runner++;
		save = if_rdrct_quotes(runner);
		if (save == 0)
			return (0);
		if (save != runner)
			runner = save;
		else
		{
			save = if_or_and_pipe(runner);
			if (save == 0)
				return (0);
			else if (save == runner)
				runner++;
			else if (save != runner)
				runner = save;
		}
	}
	return (1);
}