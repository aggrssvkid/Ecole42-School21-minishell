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

static char	*find_close(char *runner)
{
	if (*runner == '"')
	{
		runner++;
		while (*runner != '\0')
		{
			if (*runner == '"')
				return (++runner);
			runner++;
		}
	}
	else if (*runner == '\'')
	{
		runner++;
		while (*runner != '\0')
		{
			if (*runner == '\'')
				return (++runner);
			runner++;
		}
	}
	return (0);
}

char	*syntax_quotes(char *runner)
{
	runner = find_close(runner);
	if (runner == 0)
	{
		ft_putstr_fd \
		("mshell: syntax error: unclosed q NE OBRABATIVAEM, izvini:(\n", 2);
		return (0);
	}
	return (runner);
}