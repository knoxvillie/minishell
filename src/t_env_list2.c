/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:37:33 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/24 10:37:27 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_value_from_key(t_env *env, char *key)
{
	t_env	*node;
	char	*str;

	node = env;
	while (node)
	{
		if (abs_string_cmp(key, node->key))
		{
			str = ft_strdup(node->value);
			return (str);
		}
		node = node->next;
	}
	return (NULL);
}

void	modify_value(t_msh *data, char *key, char **new_value)
{
	t_env	*node;

	node = data->ppt->list;
	while (node)
	{
		if (abs_string_cmp(key, node->key))
		{
			free (node->value);
			node->value = *new_value;
			return ;
		}
		node = node->next;
	}
}

bool	is_key_in_env(t_env *env, char *key)
{
	while (env)
	{
		if (abs_string_cmp(key, env->key))
			return (true);
		env = env->next;
	}
	return (false);
}

/*
char	*get_key_address(t_env *env, char *key)
{
	while (env)
	{
		if (abs_string_cmp(key, env->key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
*/
