/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:50:56 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/12 16:08:19 by kfaustin         ###   ########.fr       */
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
	if (str[i] && str[i] == '=')
	{
		if (str[i - 1] == ' ' || str[i + 1] == ' ')
		{
			ft_putstr_fd("minishell: Export: not a valid identifier\n", 2);
			return (false);
		}
	}
	return (true);
}

// str must be handled before the func to prevent unclosed quotes: ARG='kelvin"
void	builtin_export(t_msh *data)
{
	int		i;
	char	**table;
	char	*value;
	t_env	*node;

	i = 0;
	while (data->lst_cmd->argList[++i]) //problemas com espaços!
	{
		if (!check_syntax_var_equal(data->lst_cmd->argList[i]))
			continue ;
		table = ft_split(data->lst_cmd->argList[i], '=');
		value = table[1];
		if (!value)
			value = ft_strdup("\0");
		node = init_env_node(table[0], value);
		data->ppt->list = stack_env_list(data->ppt->list, node);
		free (table);
	}
}