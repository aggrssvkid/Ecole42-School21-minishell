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

static void	get_pwd(t_env *our_env, char *new_key, char *new_value)
{
	t_node	*finder;
	char	buf[1000];

	finder = our_env->head;
	while (finder != 0 && ft_strcmp("PWD", finder->key) != 0)
		finder = finder->next;
	if (finder == 0)
	{
		new_key = ft_strdup("PWD");
		getcwd(buf, 1000);
		new_value = ft_strdup(buf);
		add_new_env_node(our_env, new_key, new_value);
	}
	else
	{
		free(finder->value);
		getcwd(buf, 1000);
		new_value = ft_strdup(buf);
		finder->value = new_value;
	}
}

static void	up_shell_lvl(t_env *our_env, char *new_key, char *new_value)
{
	t_node	*finder;
	int		lvl;

	finder = our_env->head;
	while (finder != 0 && ft_strcmp("SHLVL", finder->key) != 0)
		finder = finder->next;
	if (finder == 0)
	{
		new_key = ft_strdup("SHLVL");
		new_value = ft_strdup("1");
		add_new_env_node(our_env, new_key, new_value);
	}
	else
	{
		lvl = ft_atoi(finder->value) + 1;
		free(finder->value);
		finder->value = ft_itoa(lvl);
	}
}

void	env_update_params(t_env *our_env)
{
	char	*new_key;
	char	*new_value;

	new_key = 0;
	new_value = 0;
	up_shell_lvl(our_env, new_key, new_value);
	get_pwd(our_env, new_key, new_value);
}
