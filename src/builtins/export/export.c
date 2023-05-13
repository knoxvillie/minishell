/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:50:56 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/11 11:00:07 by kfaustin         ###   ########.fr       */
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
			printf("TEMP MSG: Export invalid syntax\n"); // Trocar func to print_exit dandos os devidos frees.
			return (false);
		}
		i++;
	}
	if (str[i])
	{
		if (str[i - 1] == ' ' || str[i + 1] == ' ')
		{
			printf("TEMP MSG: Export invalid syntax () not alpha num\n"); // Trocar func to print_exit dandos os devidos frees.
			return (false);
		}
	}
	return (true);
}

// str must be handled before the func to prevent unclosed quotes: ARG='kelvin"
void	builtin_export(t_msh *data)
{
	char	**table;
	char	*value;
	char	*arg;
	t_env	*node;

	arg = data->lst_cmd->argv[1];
	if (!check_syntax_var_equal(arg))
		return ;
	table = ft_split(arg, '=');
	value = table[1];
	if (!value)
		value = ft_strdup("\0");
	node = init_env_node(table[0], value);
	data->ppt->list = stack_env_list(data->ppt->list, node);
	free (table);
}