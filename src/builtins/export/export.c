/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:50:56 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/27 19:08:42 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	export_only(t_msh *data)
{
	t_env	*env;
	t_env	*exp;

	env = data->export->env;
	exp = data->export->exp;
	while (env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->key, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(env->value, 1);
		ft_putstr_fd("\"\n", 1);
		env = env->next;
	}
	while (exp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(exp->key, 1);
		ft_putstr_fd("\n", 1);
		exp = exp->next;
	}
}

static void	export_export(t_msh *data, char *str)
{
	t_env	*node;
	char	*key;

	key = ft_strdup(str);
	node = init_env_node(key, NULL);
	data->export->exp = stack_env_list(data->export->exp, node);
}

static bool	check_syntax_var_equal(t_msh *data, char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '=' && i != 0)
			break ;
		if (!is_alnumunder(str[i]))
		{
			ft_putstr_fd("msh: Export: not a valid identifier\n", 2);
			return (false);
		}
	}
	if (str[i] == '\0')
	{
		export_export(data, str);
		return (false);
	}
	return (true);
}

static void	do_export(t_msh *data, char *arg)
{
	char	**table;
	char	*value;
	char	*key;
	t_env	*node;

	table = ft_split(arg, '=');
	key = ft_strdup(table[0]);
	if (table[1] == NULL)
		value = ft_strdup("\0");
	else
		value = ft_strdup(table[1]);
	free_table(table);
	if (is_key_in_env(data->ppt->list, key))
		return (modify_value(data, key, &value), free(key));
	if (is_key_in_env(data->export->exp, key))
		ft_unset(data, key);
	node = init_env_node(key, value);
	data->ppt->list = stack_env_list(data->ppt->list, node);
}

void	builtin_export(t_msh *data)
{
	int		i;
	char	*str;

	str = data->lst_cmd->argv[1];
	if (str == NULL)
		return (export_only(data));
	if (abs_string_cmp(str, "#"))
		return (export_only(data));
	i = 0;
	while (data->lst_cmd->argv[++i])
	{
		str = data->lst_cmd->argv[i];
		if (!check_ue_syntax(str, "export"))
			continue ;
		if (!check_syntax_var_equal(data, str))
			continue ;
		do_export(data, str);
	}
	free_table(data->env);
	init_env_table(data);
	g_exit_status = 0;
}
