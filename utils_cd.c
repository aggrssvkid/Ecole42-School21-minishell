/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:39:45 by anemesis          #+#    #+#             */
/*   Updated: 2022/05/31 16:06:07 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft/libft.h"

void	get_paths(char ***oldpwd, char ***pwd, char ***home, t_env *list)
{
	t_node	*tmp;

	tmp = find_node_by_key("OLDPWD", list);
	*oldpwd = NULL;
	if (tmp)
		*oldpwd = &tmp->value;
	tmp = find_node_by_key("PWD", list);
	*pwd = NULL;
	if (tmp)
		*pwd = &tmp->value;
	tmp = find_node_by_key("HOME", list);
	*home = NULL;
	if (tmp)
		*home = &tmp->value;
}

void	refresh_wd_paths(char **oldpwd, char **pwd)
{
	if (pwd != NULL)
	{
		if (oldpwd != NULL)
		{
			free(*oldpwd);
			*oldpwd = *pwd;
		}
		else
			free(*pwd);
		*pwd = getcwd(NULL, 0);
	}
	else if (oldpwd != NULL)
	{
		free(*oldpwd);
		*oldpwd = ft_strdup("");
	}
	else
		return ;
}
