/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:46:51 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/05/21 19:45:57 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	do_cd(t_msh *data, char	**var_home);

static void	go_back(t_msh *data, char **str)
{
	char	*next_pwd;
	char	*actual_pwd;

	free (*str);
	if (data->lst_cmd->argv[1][1] != '\0')
		return ;
	next_pwd = get_value_from_key(data->ppt->list, "OLDPWD");
	if (chdir(next_pwd) != 0)
	{
		free (next_pwd);
		return ;
	}
	actual_pwd = get_value_from_key(data->ppt->list, "PWD");
	modify_value(data, "OLDPWD", &actual_pwd);
	modify_value(data, "PWD", &next_pwd);
}

static void	go_home_up(t_msh *data)
{
	char	*home;

	home = get_value_from_key(data->ppt->list, "HOME");
	if (!home)
		return ;
	do_cd(data, &home);
}

static void	do_cd(t_msh *data, char	**var_home)
{
	char	*next_pwd;
	char	*actual_pwd;

	if (!var_home)
	{
		next_pwd = do_dot(data);
		if (abs_string_cmp(next_pwd, "-"))
			return (go_back(data, &next_pwd));
	}
	else
		next_pwd = *var_home;
	if (chdir(next_pwd) != 0)
	{
		free (next_pwd);
		return ;
	}
	actual_pwd = get_value_from_key(data->ppt->list, "PWD");
	modify_value(data, "OLDPWD", &actual_pwd);
	modify_value(data, "PWD", &next_pwd);
}

void	builtin_cd_update(t_msh *data)
{
	int	n_cmd;

	n_cmd = 0;
	while (data->lst_cmd->argv[n_cmd])
		n_cmd++;
	if (n_cmd > 2)
		return ;
	if (n_cmd == 1)
		go_home_up(data);
	if (n_cmd == 2)
		do_cd(data, NULL);
	free_table(data->env);
	init_env_table(data);
}