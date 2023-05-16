/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:25:43 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/16 10:47:01 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
// Returns true if the var to unset was located and freed in the key of the first node
static bool	check_unset_first_node(t_env *env, char *str)
{
	t_env	*tmp;

	if (abs_string_cmp(str, env->key))
	{
		free (env->key);
		free (env->value);
		tmp = env->next;
		free (env);
		env = tmp;
		return (true);
	}
	return (false);
}

// Returns true if the var to unset was located and freed until the end os the env.
static bool	check_unset_till_end(t_env *env, char *str)
{
	t_env	*header;
	t_env	*tmp;

	header = env;
	while (env)
	{
		if (abs_string_cmp(str, env->key))
		{
			free (env->key);
			free (env->value);
			tmp->next = env->next;
			free (env);
			env = header;
			return (true);
		}
		tmp = env;
		env = env->next;
	}
	env = header;
	return (false);
}

void	builtin_unset(t_msh *data)
{
	char	*str;

	str = (char *)data->lst_cmd->argv[1];
	if (check_unset_first_node(data->ppt->list, str))
	{
		free_t_env(data->ppt->list);
		init_env_table(data);
		return ;
	}

	if (check_unset_till_end(data->ppt->list, str))
	{
		free_t_env(data->ppt->list);
		init_env_table(data);
		return ;
	}
}