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
#include "get_next_line.h"

static char	*heredoc_random(char *here_doc, t_evrything *all, char *filename)
{
	char	*helper;
	char	*join;
	char	*name;

	name = ft_strjoin("<", filename);
	helper = name;
	*here_doc = '\0';
	join = ft_strjoin(all->str, name);
	free(helper);
	*here_doc = '<';
	helper = join;
	all->str = ft_strjoin(join, all->end);
	free(helper);
	return (all->str);
}

static void	heredoc_gnl(t_evrything *all, char *stop_word, int fd)
{
	char	*get_line;

	get_line = get_next_line(0);
	if (get_line != 0 && ft_strcmp(get_line, stop_word) != 0)
		get_line = parse_dollar(get_line, all->our_env);
	while (get_line != 0 && ft_strcmp(get_line, stop_word) != 0)
	{
		write(fd, get_line, ft_strlen(get_line));
		free(get_line);
		get_line = get_next_line(0);
		if (get_line == 0)
		{
			free(get_line);
			return ;
		}
		if (ft_strcmp(get_line, stop_word) != 0)
			get_line = parse_dollar(get_line, all->our_env);
	}
	free(get_line);
}

char	*heredoc_exchange(char *here_doc, int i, t_evrything *all)
{
	char	*stop_word;
	char	*helper;
	int		fd;

	stop_word = here_doc + 2;
	while (*stop_word == ' ')
		stop_word++;
	all->end = stop_word + 1;
	while (check_split_symbol(all->end) == 0)
		all->end++;
	all->tmp = *all->end;
	*all->end = '\0';
	stop_word = parse_find_word(stop_word);
	helper = stop_word;
	stop_word = ft_strjoin(stop_word, "\n");
	free(helper);
	fd = open (all->heredoc_names[i], O_CREAT + O_RDWR + O_TRUNC, 0644);
	heredoc_gnl(all, stop_word, fd);
	close(fd);
	free(stop_word);
	*all->end = all->tmp;
	all->str = heredoc_random(here_doc, all, all->heredoc_names[i]);
	return (all->str);
}
