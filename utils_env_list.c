/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 22:10:52 by anemesis          #+#    #+#             */
/*   Updated: 2022/06/01 15:58:50 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft/libft.h"

/**
	"add_new_env_line" allocates and links new list node and frees input "key" and
	"value" pointers
**/
void	add_new_env_node(t_env *env_list, char *key, char *value)
{
	t_node	*new_node;

	new_node = malloc(sizeof(*new_node));
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	if (env_list->size == EMPTY)
	{
		env_list->head = new_node;
		env_list->tail = new_node;
		new_node->prev = NULL;
	}
	else
	{
		new_node->prev = env_list->tail;
		env_list->tail->next = new_node;
		env_list->tail = new_node;
	}
	env_list->size++;
}

/**
	"copy_env" creates list structure from strings array, setting "key" and "value"
	fields of each list node to substrings of each input string delimeted by '=',
	returns list structure
**/
t_env	copy_env(char **env)
{
	t_env	env_list;
	int		i;
	char	**tmp;

	env_list.size = 0;
	env_list.head = NULL;
	env_list.tail = NULL;
	i = 0;
	while (env[i])
	{
		tmp = ft_split(env[i], '=');
		add_new_env_node(&env_list, tmp[KEY], tmp[VALUE]);
		free(tmp);
		i++;
	}
	return (env_list);
}

/**
	"find_node_by_key" searches for node in list, which "key" field corresponds
	to "key" argument string, and returns pointer to that node or returns NULL if
	there is no such key in list
**/
t_node	*find_node_by_key(char *key, t_env *env_list)
{
	t_node	*tmp;

	tmp = env_list->head;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == EQUAL)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

/**
	"destroy_env_list" frees memory allocated for t_env list
**/
void	destroy_env_list(t_env *env_list)
{
	t_node	*node_to_free;
	t_node	*tmp_node;

	tmp_node = env_list->head;
	while (tmp_node)
	{
		node_to_free = tmp_node;
		tmp_node = tmp_node->next;
		free(node_to_free->key);
		free(node_to_free->value);
		free(node_to_free);
	}
}

char	**list_to_array(t_env *env_list)
{
	char	**env_array;
	t_node	*tmp_node;
	char	**array_head;
	char	*tmp_str;

	env_array = malloc(sizeof(*env_array) * env_list->size);
	array_head = env_array;
	tmp_node = env_list->head;
	while (tmp_node)
	{
		tmp_str = ft_strjoin(tmp_node->key, "=");
		*env_array = ft_strjoin(tmp_str, tmp_node->value);
		free(tmp_str);
		tmp_node = tmp_node->next;
		env_array++;
	}
	*env_array = NULL;
	return (array_head);
}
