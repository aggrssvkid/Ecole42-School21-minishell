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

char	*syntax_left_rdrct(char *runner)
{
	if (*(runner + 1) == '<' || *(runner + 1) == '>')
		runner = runner + 2;
	else
		runner++;
	while (*runner == ' ')
		runner++;
	if (*runner == '|' || *runner == '<' || *runner == '>' || *runner == '&' || *runner == '\0')
	{
		ft_putstr_fd("mshell: syntax error:", 2);
		ft_putstr_fd \
		(" bud chelovekom, poprobuy ewe razok!(kak v tom anekdote)\n", 2);
		return (0);
	}
	return (runner);
}

char	*syntax_logic_and(char *runner)
{
	if (*(runner + 1) != '&')
	{
		ft_putstr_fd("mshell: syntax error:  tolko dva & prinimaem:(\n", 2);
		return (0);
	}
	else
		runner = runner + 2;
	while (*runner == ' ')
		runner++;
	if (*runner == '|' || *runner == '&' || *runner == '\0')
	{
		ft_putstr_fd("mshell: syntax error:", 2);
		ft_putstr_fd(" ne ne ne DAVID BLANE, takie focusi ne prokatyat!\n", 2);
		return (0);
	}
	return (runner);
}

char	*syntax_logic_or(char *runner)
{
	runner = runner + 2;
	while (*runner == ' ')
		runner++;
	if(*runner == '|' || *runner == '&' || *runner == '\0')
	{
		ft_putstr_fd("mshell: syntax error: vvedi norm stroku, zaebal!\n", 2);
		return (0);
	}
	return (runner);
}

char	*syntax_pipe(char *runner)
{
	runner++;
	while (*runner == ' ')
		runner++;
	if(*runner == '|' || *runner == '&' || *runner == '\0')
	{
		ft_putstr_fd("mshell: syntax error: nu skolko mojno,", 2);
		ft_putstr_fd(" clown?! DAVAY ZANOGO VVODI STR!\n", 2);
		return (0);
	}
	return (runner);
}

char	*syntax_right_rdrct(char *runner)
{
	if (*(runner + 1) == '>')
		runner = runner + 2;
	else
		runner++;
	while (*runner == ' ')
		runner++;
	if (*runner == '|' || *runner == '<' || *runner == '>' || *runner == '&' || *runner == '\0')
	{
		ft_putstr_fd("mshell: syntax error: gospodi, ", 2); 
		ft_putstr_fd("ti sovsem obdolbalsya uje?! Go again...\n", 2);
		return (0);
	}
	return (runner);
}