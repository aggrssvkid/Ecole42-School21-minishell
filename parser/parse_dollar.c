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

int	check_single_in_double(char *dollar)
{
	char	*last_solo;
	char	*runner;
	int		d_quotes;

	runner = dollar;
	while (*runner != '\0')
	{
		if (*runner == '\'')
			last_solo = runner;
		runner++;
	}
	runner = last_solo;
	d_quotes = 0;
	while (*runner != '\0')
	{
		runner++;
		if (*runner == '"')
			d_quotes++;
	}
	if (d_quotes % 2 == 0)
		return (0);
	return (1);
}

static char	*check_next_symbol(char *exchange, char *runner, t_env our_env)
{
	if (*(runner + 1) >= '0' && *(runner + 1) <= '9')
		exchange = digit_dollar(exchange, runner);
	else if (*(runner + 1) == '$')
		exchange = idi_v_zad(exchange, runner);
	else if (*(runner + 1) == '?')
		exchange = dollar_vopros(exchange, runner);
	else if ((*(runner + 1) >= 'a' && *(runner + 1) <= 'z') || (*(runner + 1) >= 'A' && *(runner + 1) <= 'Z') || *(runner + 1) == '_')
		exchange = good_arg_value(exchange, runner, our_env);
	else
		return (exchange);
	return (exchange);
}

static int	check_dollar_not_in_single(char *symbol)
{
	int	single_quotes;

	single_quotes = 0;
	while (*symbol != '\0')
	{
		symbol++;
		if (*symbol == '\'')
			single_quotes++;
	}
	if (single_quotes % 2 == 0)
		return (1);
	return (0);
}

char	*parse_dollar(char *command, t_env our_env)
{
	char	*runner;
	char	*exchange;
	char	*ptr_free;

	runner = command;
	exchange = command;
	while (*runner != '\0')
	{
		if (*runner == '$' && check_symbol_not_in_quotes(runner) == 1 && *(runner + 1) == '"')
		{
			ptr_free = exchange;
			exchange = parse_dollar_if_next_quotes(exchange, runner);
			free(ptr_free);
			runner = exchange;
		}
		else if (*runner == '$' && check_symbol_not_in_quotes(runner) == 1 && *(runner + 1) == '\'')
		{
			ptr_free = exchange;
			exchange = parse_dollar_if_next_quotes(exchange, runner);
			free(ptr_free);
			runner = exchange;
		}
		if ((*runner == '$' && check_dollar_not_in_single(runner) == 1) || (*runner == '$' && check_dollar_not_in_single(runner) == 0 && check_single_in_double(runner) == 1))
		{
			ptr_free = exchange;
			exchange = check_next_symbol(exchange, runner, our_env);
			if (exchange == 0)
			{
				free(ptr_free);
				return (0);
			}
			if (ptr_free != exchange)
			{
				free(ptr_free);
				runner = exchange;
			}
			else
				runner++;
		}
		else
			runner++;
	}
	return (exchange);
}