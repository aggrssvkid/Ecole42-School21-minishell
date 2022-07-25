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

char	*join_split_word(char **split_word)
{
	int i;

	char	*helper;
	char	*new_word;

	i = 0;
	new_word = ft_strdup(split_word[i]);
	i++;
	if (split_word[i] == 0)
		return (new_word);
	while (split_word[i] != 0)
	{
		helper = new_word;
		new_word = ft_strjoin(new_word, split_word[i]);
		i++;
		free(helper);
	}
	return (new_word);
}

char	**go_split_word(char **split_word, char *word)
{
	char	*runner;
	char	*start;
	char	tmp;
	int		i;

	runner = word;
	i = 0;
	while (*runner != '\0')
	{
		if (*runner == '"' && check_symbol_not_in_quotes(runner) == 1)
		{
			runner++;
			start = runner;
			while (*runner != '"')
				runner++;
			*runner = '\0';
			split_word[i] = ft_strdup(start);
			i++;
			*runner = '"';
			runner++;
		}
		else if(*runner == '\'' && check_symbol_not_in_quotes(runner) == 1)
		{
			runner++;
			start = runner;
			while (*runner != '\'')
				runner++;
			*runner = '\0';
			split_word[i] = ft_strdup(start);
			i++;
			*runner = '\'';
			runner++;
		}
		else
		{
			start = runner;
			while (*runner != '\0' && *runner != '\'' && *runner != '"')
				runner++;
			tmp = *runner;
			*runner = '\0';
			split_word[i] = ft_strdup(start);
			i++;
			*runner = tmp;
		}
	}
	split_word[i] = 0;
	return (split_word);
}

static int	find_num_words(char *word)
{
	char	*runner;
	int		num_words;

	runner = word;
	num_words = 0;
	while (*runner != '\0')
	{
		if (*runner == '"' && check_symbol_not_in_quotes(runner) == 1)
		{
			runner++;
			while (*runner != '"')
				runner++;
			runner++;
		}
		else if (*runner == '\'')
		{
			runner++;
			while (*runner != '\'')
				runner++;
			runner++;
		}
		else
		{
			while (*runner != '\0' && *runner != '"'  && *runner != '\'' )
				runner++;
		}
		num_words++;
	}
	return (num_words);
}

static char	*exchange_word(char *word)
{
	int		num_words;
	char	**split_word;
	char	*new_word;

	num_words = find_num_words(word);
	split_word = malloc((1 + num_words) * sizeof(char *));
	if (split_word == 0)
	{
		write(1, "malloc error\n", 13);
		return (0);
	}
	split_word = go_split_word(split_word, word);
	new_word = join_split_word(split_word);
	del_matrix(split_word);
	return (new_word);
}

char	*parse_find_word(char *start_symbol)
{
	char	*end_symbol;
	char	*word;
	char	*new_word;
	char	tmp;

	end_symbol = start_symbol;
	while (check_split_symbol(end_symbol) == 0)
		end_symbol++;
	tmp = *end_symbol;
	*end_symbol = '\0';
	word = ft_strdup(start_symbol);
	if (word == 0)
		return (0);
	*end_symbol = tmp;
	new_word = exchange_word(word);
	free(word);
	return (new_word);
}