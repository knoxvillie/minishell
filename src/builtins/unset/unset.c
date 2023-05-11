/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:25:43 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/03 15:03:04 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
// Returns true if the var to unset was located and freed in the key of the first node
static bool	check_unset_first_node(t_env *env, char *str, int len_str)
{
	t_env	*tmp;
	int		len_key;

	len_key = (int)ft_strlen(env->key);
	if ((len_str == len_key) && !ft_strncmp(str, env->key, len_str))
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
static bool	check_unset_till_end(t_env *env, char *str, int len_str)
{
	t_env	*header;
	t_env	*tmp;
	int		len_key;

	header = env;
	while (env)
	{
		len_key = (int)ft_strlen(env->key);
		if ((len_str == len_key) && !ft_strncmp(str, env->key, len_str))
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

// Be sure that env is not null
void	builtin_unset(t_msh *data)
{
	char	*str;
	int		len_str;

	str = (char *)data->lst_cmd->argList[1];
	len_str = (int)ft_strlen(str);
	if (check_unset_first_node(data->ppt->list, str, len_str))
		return ;
	if (check_unset_till_end(data->ppt->list, str, len_str))
		return ;
	// Print to tests only, TO DELETE!
	ft_putstr_fd("key not found in env list, nothing to unset\n", 2);
}