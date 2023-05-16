/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:25:43 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/16 12:37:20 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	check_exp_first_node(t_env *exp, char *str)
{
	t_env	*tmp;

	if (abs_string_cmp(str, exp->key))
	{
		free (exp->key);
		tmp = exp->next;
		free (exp);
		exp = tmp;
		return (true);
	}
	return (false);
}

static bool	check_exp_till_end(t_env *exp, char *str)
{
	t_env	*header;
	t_env	*tmp;

	header = exp;
	while (exp)
	{
		if (abs_string_cmp(str, exp->key))
		{
			free (exp->key);
			tmp->next = exp->next;
			free (exp);
			exp = header;
			return (true);
		}
		tmp = exp;
		exp = exp->next;
	}
	exp = header;
	return (false);
}

static bool	check_env_first_node(t_env *env, char *str)
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

static bool	check_env_till_end(t_env *env, char *str)
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
	int		i;

	str = data->lst_cmd->argv[1];
	if (str == NULL)
		return ;
	i = 0;
	while (++i)
	{
		if (check_env_first_node(data->export->env, str))
			continue ;
		if (check_env_till_end(data->export->env, str))
			continue ;
		if (check_exp_first_node(data->export->exp, str))
			continue ;
		if (check_exp_till_end(data->export->exp, str))
			continue ;
	}
	free_table(data->env);
	init_env_table(data);
}