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

char	**heredoc_get_names(int nbr_diff_heredoc)
{
	int		i;
	char	*nbr;
	char	**names;

	i = 0;
	names = malloc((1 + nbr_diff_heredoc) * sizeof(char *));
	if (names == 0)
	{
		ft_putstr_fd("MALLOC ERROR!\n", 2);
		exit(EXIT_FAILURE);
	}
	names[nbr_diff_heredoc] = 0;
	while (i < nbr_diff_heredoc)
	{
		nbr = ft_itoa(i);
		if (nbr == 0)
		{
			ft_putstr_fd("MALLOC ERROR!\n", 2);
			exit(EXIT_FAILURE);
		}
		names[i] = ft_strjoin("RANDOMFILE", nbr);
		free(nbr);
		i++;
	}
	return (names);
}

int	heredoc_diff_nbr(char *str)
{
	int		nbr_diff_heredoc;
	char	*runner;

	nbr_diff_heredoc = 0;
	runner = str;
	while (*runner != '\0')
	{
		if (*runner == '<' && check_symbol_not_in_quotes(runner) == 1 \
		&& *(runner + 1) == '<')
		{
			nbr_diff_heredoc++;
			while (*runner != '\0' && (*runner != '&' || \
			check_symbol_not_in_quotes(runner) == 0) && \
			(*runner != '|' || *(runner + 1) != '|' || \
			check_symbol_not_in_quotes(runner) == 0))
				runner++;
			if (*runner != '\0')
				runner = runner + 2;
		}
		else
			runner++;
	}
	return (nbr_diff_heredoc);
}
