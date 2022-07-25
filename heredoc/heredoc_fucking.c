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

int	find_heredoc(char *runner)
{
	while (*runner != '\0')
	{
		if (*runner == '<' && check_symbol_not_in_quotes(runner) \
		&& *(runner + 1) == '<')
			return (1);
		else if ((*runner == '|' && check_symbol_not_in_quotes(runner) \
		&& *(runner + 1) == '|') || (*runner == '&' && \
		check_symbol_not_in_quotes(runner) && *(runner + 1) == '&'))
			return (0);
		runner++;
	}
	return (0);
}

static void	exchange(t_evrything *all, char *helper, int i)
{
	i++;
	i--;
	helper = all->str;
	all->str = heredoc_exchange(all->runner, i, all);
	free(helper);
	all->runner = all->str;
}

void	heredoc_fucking(t_evrything *all)
{
	int		i;
	char	*helper;

	i = 0;
	all->runner = all->str;
	helper = 0;
	while (*all->runner != '\0')
	{
		if (*all->runner == '<' && check_symbol_not_in_quotes(all->runner) \
		== 1 && *(all->runner +1) == '<')
			exchange(all, helper, i);
		else if ((*all->runner == '&' && \
		check_symbol_not_in_quotes(all->runner) == 1) || (*all->runner == '|' \
		&& check_symbol_not_in_quotes(all->runner) == \
		1 && *(all->runner + 1) == '|'))
		{
			all->runner = all->runner + 2;
			if (find_heredoc(all->runner) == 1)
				i++;
		}
		else
			all->runner++;
	}
}
