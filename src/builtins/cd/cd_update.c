/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:46:51 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/05/24 09:38:23 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	do_cd_up(t_msh *data);

static void	go_back_up(t_msh *data)
{
	char	*next_pwd;
	char	*actual_pwd;

	next_pwd = get_value_from_key(data->ppt->list, "OLDPWD");
	if (chdir(next_pwd) != 0)
		return (free (next_pwd));
	actual_pwd = get_value_from_key(data->ppt->list, "PWD");
	modify_value(data, "OLDPWD", &actual_pwd);
	modify_value(data, "PWD", &next_pwd);
}

static void	go_home_up(t_msh *data)
{
	char	*home;
	char	*actual_pwd;

	home = get_value_from_key(data->ppt->list, "HOME");
	if (!home)
		return (free(home));
	if (chdir(home) != 0)
		return (free (home));
	actual_pwd = get_value_from_key(data->ppt->list, "PWD");
	modify_value(data, "OLDPWD", &actual_pwd);
	modify_value(data, "PWD", &home);
}

static void	do_cd_up(t_msh *data)
{
	char	*next_pwd;
	char	*actual_pwd;

	next_pwd = ft_strdup(data->lst_cmd->argv[1]);
	if (abs_string_cmp(next_pwd, "-"))
		return (free (next_pwd), go_back_up(data));
	if (abs_string_cmp(next_pwd, "~"))
		return (free (next_pwd), go_home_up(data));
	if (chdir(next_pwd) != 0)
		return (free (next_pwd));
	free (next_pwd);
	next_pwd = getcwd(NULL, 0);
	actual_pwd = get_value_from_key(data->ppt->list, "PWD");
	modify_value(data, "OLDPWD", &actual_pwd);
	modify_value(data, "PWD", &next_pwd);
}

void	builtin_cd_update(t_msh *data)
{
	int	number_cmds;

	number_cmds = 0;
	while (data->lst_cmd->argv[number_cmds])
		number_cmds++;
	if (number_cmds > 2)
		return ;
	if (number_cmds == 1)
		go_home_up(data);
	if (number_cmds == 2)
		do_cd_up(data);
}
