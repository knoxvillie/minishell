/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:37:33 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/04 10:15:58 by kfaustin         ###   ########.fr       */
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

bool	abs_string_cmp(char *s1, char *s2)
{
	int		len_s1;
	int		len_s2;

	len_s1 = (int)ft_strlen(s1);
	len_s2 = (int) ft_strlen(s2);
	if ((len_s1 == len_s2) && !ft_strncmp(s1, s2, len_s1))
		return (true);
	return (false);
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
