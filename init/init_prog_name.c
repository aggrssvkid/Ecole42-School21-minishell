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

static char	*move_runner(char *runner)
{
	if (*runner == '>' && *(runner + 1) == '>')
		runner = runner + 2;
	else if (*runner == '<' && *(runner + 1) == '>')
		runner = runner + 2;
	else
		runner++;
	while (*runner == ' ')
		runner++;
	while (check_split_symbol(runner) == 0)
		runner++;
	return (runner);
}

static char	*get_prog_name(char *start_symbol)
{
	char	*name;

	name = parse_find_word(start_symbol);
	if (name == 0)
		return (0);
	return (name);
}

char	*init_prog_name(char *command)
{
	char	*runner;
	char	*prog_name;

	prog_name = 0;
	runner = command;
	while (*runner != '\0')
	{
		while (*runner == ' ')
			runner++;
		if (check_split_symbol(runner) == 0)
		{
			prog_name = get_prog_name(runner);
			if (prog_name == 0)
				return (0);
			return (prog_name);
		}
		else
			runner = move_runner(runner);
	}
	return (prog_name);
}
