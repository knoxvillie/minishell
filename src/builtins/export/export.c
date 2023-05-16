/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:50:56 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/16 11:27:14 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	check_syntax_var_equal(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]))
		{
			ft_putstr_fd("minishell: Export: not a valid identifier\n", 2);
			return (false);
		}
		i++;
	}
	if (!str[i])
		return (false);
	if (str[i] == '=' && i == 0)
		return (false);
	return (true);
}

static void	do_export(t_msh *data, char *arg)
{
	char	**table;
	char	*value;
	t_env	*node;

	table = ft_split(arg, '=');
	value = table[1];
	if (value == NULL)
		value = ft_strdup("\0");
	if (is_key_in_env(data->ppt->list, table[0]))
	{
		modify_value(data, table[0], &value);
		free (table);
		return ;
	}
	node = init_env_node(table[0], value);
	data->ppt->list = stack_env_list(data->ppt->list, node);
	free (table);
}

void	builtin_export(t_msh *data)
{
	int		i;

	if (data->lst_cmd->argv[1] == NULL)
		return ;
	i = 0;
	while (data->lst_cmd->argv[++i])
	{
		if (!check_syntax_var_equal(data->lst_cmd->argv[i]))
			continue ;
		do_export(data, data->lst_cmd->argv[i]);
	}
	free_table(data->env);
	init_env_table(data);
}