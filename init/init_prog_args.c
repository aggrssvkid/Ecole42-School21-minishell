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
	if (*runner == '\0')
		return (runner);
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

static char	**get_base_args(char *command, char **prog_args)
{
	int	i;

	i = 0;
	while (*command != '\0')
	{
		while (*command == ' ')
			command++;
		if (check_split_symbol(command) == 0)
		{
			prog_args[i] = parse_find_word(command);
			if (prog_args[i] == 0)
				exit(EXIT_FAILURE);
			i++;
			while (check_split_symbol(command) == 0)
				command++;
		}
		else
			command = move_runner(command);
	}
	prog_args[i] = 0;
	return (prog_args);
}

static int	num_no_rdrct_args(char *command)
{
	char	*runner;
	int		num_args;

	runner = command;
	num_args = 0;
	while (*runner != '\0')
	{
		while (*runner == ' ')
			runner++;
		if (check_split_symbol(runner) == 0)
		{
			num_args++;
			runner++;
			while (check_split_symbol(runner) == 0)
				runner++;
		}
		else
			runner = move_runner(runner);
	}
	return (num_args);
}

char	**init_prog_args(char *command)
{
	char	**prog_args;
	int		num_args;

	num_args = num_no_rdrct_args(command);
	prog_args = malloc((num_args + 1) * sizeof(char *));
	prog_args = get_base_args(command, prog_args);
	return (prog_args);
}
