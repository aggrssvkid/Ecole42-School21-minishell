/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:29:10 by anemesis          #+#    #+#             */
/*   Updated: 2022/06/01 16:02:43 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft/libft.h"

int	is_all_chars_valid(char *str)
{
	while (*str)
	{
		if (((int)*str < 65 && (int)*str > 32 && (int)*str != 43)
			|| ((int)*str < 95 && (int)*str > 90)
			|| ((int)*str < 128 && (int)*str > 122)
			|| ((int)*str == 96))
			return (1);
		str++;
	}
	return (0);
}

char	**split_by_first_occur(char	const	*s, char c)
{
	char	**all_split;
	char	**pair;

	pair = malloc(sizeof(*pair) * 2);
	if (!pair)
		exit(EXIT_FAILURE);
	all_split = ft_split(s, c);
	pair[KEY] = all_split[0];
	pair[VALUE] = all_split[1];
	if (ft_strchr(s, c))
	{
		free(pair[VALUE]);
		pair[VALUE] = ft_strdup(ft_strchr(s, c) + 1);
	}
	free(all_split);
	return (pair);
}

void	ft_perror(int count, ...)
{
	va_list	ptr;

	va_start(ptr, count);
	while (count > 0)
	{
		ft_putstr_fd(va_arg(ptr, char *), 1);
		count--;
	}
	va_end(ptr);
	perror(NULL);
}
