/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:27:39 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/27 16:58:01 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	export_export_up(t_msh *data, char *str)
{
	t_env	*node;
	char	*key;

	key = ft_strdup(str);
	node = init_env_node(key, NULL);
	data->export->exp = stack_env_list(data->export->exp, node);
}

static bool	check_syntax_up(t_msh *data, char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '=' && i != 0)
			break ;
		if (!is_alnumunder(str[i]))
			return (false);
	}
	if (str[i] == '\0')
	{
		export_export_up(data, str);
		return (false);
	}
	return (true);
}

static void	do_export_up(t_msh *data, char *arg)
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
	{
		modify_value_exp(data, key, &value);
		return (free(key));
	}
	node = init_env_node(table[0], value);
	data->ppt->list = stack_env_list(data->ppt->list, node);
	free_table(table);
}

void	builtin_export_update(t_msh *data)
{
	int		i;
	char	*str;

	str = data->lst_cmd->argv[1];
	if (str == NULL)
		return ;
	if (abs_string_cmp(str, "#"))
		return ;
	i = 0;
	while (data->lst_cmd->argv[++i])
	{
		str = data->lst_cmd->argv[i];
		if (!check_ue_syntax_up(str))
			continue ;
		if (!check_syntax_up(data, str))
			continue ;
		do_export_up(data, str);
	}
}
