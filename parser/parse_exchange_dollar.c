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

int	check_no_fucking_ambigous(char *arg, char *exchange)
{
	arg = arg - 2;
	while (arg != exchange && *arg == ' ')
		arg--;
	if (*arg == '>' || *arg == '<')
		return (0);
	return (1);
}

char	*find_arg_value(char *arg, t_env our_env)
{
	t_node	*finder;

	finder = our_env.head;
	while (finder != 0)
	{
		if (ft_strcmp(arg, finder->key) == 0)
			return (finder->value);
		finder = finder->next;
	}
	return (0);
}

char	*good_arg_value(char *exchange, char *runner, t_env our_env)
{
	char	*arg;
	char	tmp;
	char	*join1;
	char	*arg_value;

	*runner = '\0';
	join1 = ft_strdup(exchange);
	if (join1 == 0)
		return (0);
	*runner = '$';
	runner++;
	arg = runner;
	while ((*runner >= 'a' && *runner <= 'z') || (*runner >= 'A' && *runner <= 'Z') || *runner == '_')
		runner++;
	tmp = *runner;
	*runner = '\0';
	arg_value = find_arg_value(arg, our_env);
	*runner = tmp;
	if (arg_value == 0)
	{
		if (check_no_fucking_ambigous(arg, exchange) == 0)
		{
			ft_putstr_fd("mshell: ", 2);
			*runner = '\0';
			ft_putstr_fd(arg - 1, 2);
			ft_putstr_fd(": ambiguous fucking redirect!!\n", 2);
			*runner =  tmp;
			free(join1);
			return (0);
		}
		exchange = ft_strjoin(join1, runner);
		free(join1);
		if (exchange == 0)
			return (0);
	}
	else
	{
		arg = ft_strjoin(join1, arg_value);
		free(join1);
		if (arg == 0)
			return (0);
		exchange = ft_strjoin(arg, runner);
		free(arg);
		if (exchange == 0)
			return (0);
	}
	return (exchange);
}

char	*dollar_vopros(char *exchange, char *runner)
{
	char	*nbr;
	char	*join2;
	char	*join1;
	char	tmp;

	tmp = *runner;
	*runner = '\0';
	join2 = runner + 2;
	nbr = ft_itoa(g_status);
	if (nbr == 0)
		return (0);
	join1 = ft_strjoin(exchange, nbr);
	free(nbr);
	*runner = tmp;
	if (join1 == 0)
		return (0);
	exchange = ft_strjoin(join1, join2);
	free(join1);
	if (exchange == 0)
		return (0);
	return (exchange);
}

char	*idi_v_zad(char *exchange, char *runner)
{
	char	*join2;
	char	*join1;
	char	tmp;

	tmp = *runner;
	*runner = '\0';
	join2 = runner + 2;
	join1 = ft_strjoin(exchange, "idi_v_zad");
	*runner = tmp;
	if (join1 == 0)
		return (0);
	exchange = ft_strjoin(join1, join2);
	free(join1);
	if (exchange == 0)
		return (0);
	return (exchange);
}

char	*digit_dollar(char *exchange, char *runner)
{
	char	*join2;
	char	tmp;

	tmp = *runner;
	*runner = '\0';
	join2 = runner + 2;
	exchange = ft_strjoin(exchange, join2);
	*runner = tmp;
	if (exchange == 0)
		return (0);
	return (exchange);
}