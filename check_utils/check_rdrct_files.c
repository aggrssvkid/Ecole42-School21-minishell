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

static char *if_got_rdrct(char *runner, char *name, int *fd_in, int n)
{
	runner = runner + 2;
	while (*runner == ' ')
		runner++;
	name = parse_find_word(runner);
	if (check_in_out_file(name, fd_in, n) == 0)
	{
		free(name);
		return (0);
	}
	free(name);
	return (runner);
}

static char	*get_rdrct_nbr(char *runner, int *nbr_rdrct)
{
	if (*(runner + 1) != '>')
	{
		runner++;
		*nbr_rdrct = 1;
	}
	else
	{
		runner = runner + 2;
		*nbr_rdrct = 2;
	}
	return (runner);
}

char	*if_right_rdrct(char *runner, char *name, int *fd_out, int n)
{
	int	nbr_rdrct;

	nbr_rdrct = 0;
	runner = get_rdrct_nbr(runner, &nbr_rdrct);
	while (*runner == ' ')
		runner++;
	name = parse_find_word(runner);
	if (*fd_out != 1)
		close(*fd_out);
	*fd_out = check_output_file(name, nbr_rdrct, n);
	if (*fd_out == 0)
	{
		free(name);
		return (0);
	}
	free(name);
	while (check_split_symbol(runner) == 0)
		runner++;
	return (runner);
}

char	*if_left_rdrct(char *runner, char *name, int *fd_in, int n)
{
	if (*(runner + 1) != '>')
	{
		runner++;
		while (*runner == ' ')
			runner++;
		name = parse_find_word(runner);
		if (check_input_file(name, fd_in, n) == 0)
		{
			free(name);
			return (0);
		}
		free(name);
	}
	else
		runner = if_got_rdrct(runner, name, fd_in, n);
	if (runner == 0)
		return (0);
	while (check_split_symbol(runner) == 0)
		runner++;
	return (runner);
}

int	check_rdrct_files(char	*command, int *fd_out, int *fd_in, int n)
{
	char	*runner;
	char	*name;

	runner = command;
	name = 0;
	while (*runner != '\0')
	{
		if (*runner == '<' && check_symbol_not_in_quotes(runner) == 1)
		{
			runner = if_left_rdrct(runner, name, fd_in, n);
			if (runner == 0)
				return (0);
		}
		else if (*runner == '>' && check_symbol_not_in_quotes(runner) == 1)
		{
			runner = if_right_rdrct(runner, name, fd_out, n);
			if (runner == 0)
				return (0);
		}
		else
			runner++;
	}
	return (1);
}
