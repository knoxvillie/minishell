/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:25:43 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/17 14:16:32 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	check_exp_first_node(t_msh *data, char *str)
{
	t_env	*tmp;
	t_env	*exp;

	exp = data->export->exp;
	if (exp && abs_string_cmp(str, exp->key))
	{
		free (exp->key);
		tmp = exp->next;
		free (exp);
		data->export->exp = tmp;
		return (true);
	}
	return (false);
}

static bool	check_exp_till_end(t_msh *data, char *str)
{
	t_env	*tmp;
	t_env	*exp;

	exp = data->export->exp;
	while (exp)
	{
		if (abs_string_cmp(str, exp->key))
		{
			free (exp->key);
			tmp->next = exp->next;
			free (exp);
			return (true);
		}
		tmp = exp;
		exp = exp->next;
	}
	return (false);
}

static bool	check_env_first_node(t_msh *data, char *str)
{
	t_env	*tmp;
	t_env	*env;

	env = data->export->env;
	if (env && abs_string_cmp(str, env->key))
	{
		free (env->key);
		free (env->value);
		tmp = env->next;
		free (env);
		data->export->env = tmp;
		return (true);
	}
	return (false);
}

static bool	check_env_till_end(t_msh *data, char *str)
{
	t_env	*tmp;
	t_env	*env;

	env = data->export->env;
	while (env)
	{
		if (abs_string_cmp(str, env->key))
		{
			free (env->key);
			free (env->value);
			tmp->next = env->next;
			free (env);
			return (true);
		}
		tmp = env;
		env = env->next;
	}
	return (false);
}

void	builtin_unset(t_msh *data)
{
	char	*str;
	int		i;

	if (data->lst_cmd->argv[1] == NULL) {
		return ;
	}
	i = 0;
	while (data->lst_cmd->argv[++i])
	{
		str = data->lst_cmd->argv[i];
		if (check_env_first_node(data, str))
			continue ;
		if (check_env_till_end(data, str))
			continue ;
		if (check_exp_first_node(data, str))
			continue ;
		if (check_exp_till_end(data, str))
			continue ;
	}
	free_table(data->env);
	init_env_table(data);
}