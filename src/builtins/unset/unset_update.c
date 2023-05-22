/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:48:35 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/22 14:19:17 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_unset_error(char *str, char *mode)
{
	ft_putstr_fd("msh: ", 2);
	ft_putstr_fd(mode, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

bool	check_ue_syntax(char *str, char *mode)
{
	int		i;
	bool	begin_alfa;

	i = 0;
	begin_alfa = false;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]))
		{
			print_unset_error(str, mode);
			return (false);
		}
		if (ft_isdigit(str[i]) && !begin_alfa)
		{
			print_unset_error(str, mode);
			return (false);
		}
		if (ft_isalpha(str[i]) && !begin_alfa)
			begin_alfa = true;
		i++;
	}
	return (true);
}

bool	check_ue_syntax_up(char *str)
{
	int		i;
	bool	begin_alfa;

	i = 0;
	begin_alfa = false;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]))
			return (false);
		if (ft_isdigit(str[i]) && !begin_alfa)
			return (false);
		if (ft_isalpha(str[i]) && !begin_alfa)
			begin_alfa = true;
		i++;
	}
	return (true);
}

void	builtin_unset_update(t_msh *data)
{
	char	*str;
	int		i;

	if (data->lst_cmd->argv[1] == NULL)
		return ;
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
}
