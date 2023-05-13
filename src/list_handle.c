/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:37:33 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/13 12:35:11 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_value_from_key(t_env *env, char *key)
{
	char	*str;

	while (env)
	{
		if (abs_string_cmp(key, env->key))
		{
			str = ft_strdup(env->value);
			return (str);
		}
		env = env->next;
	}
	return (NULL);
}

void	modify_value(t_msh *data, char *key, char *new_value)
{
	t_env	*node;

	node = data->ppt->list;
	while (node)
	{
		if (abs_string_cmp(key, node->key))
		{
			free (node->key);
			node->value = new_value;
			return ;
		}
		node = node->next;
	}
}

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

// Returns true if key is in env, else false.
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
