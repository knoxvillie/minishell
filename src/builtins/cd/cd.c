/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 10:47:40 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/21 21:12:52 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	do_cd(t_msh *data);

static void	go_back(t_msh *data, char **str)
{
	char	*next_pwd;
	char	*actual_pwd;

	free (*str);
	if (data->lst_cmd->argv[1][1] != '\0')
	{
		ft_putstr_fd("minishell: cd: --: invalid option\n", 2);
		return ;
	}
	next_pwd = get_value_from_key(data->ppt->list, "OLDPWD");
	if (chdir(next_pwd) != 0)
	{
		perror("chdir");
		free (next_pwd);
		return ;
	}
	actual_pwd = get_value_from_key(data->ppt->list, "PWD");
	modify_value(data, "OLDPWD", &actual_pwd);
	modify_value(data, "PWD", &next_pwd);
}

static void	go_home(t_msh *data)
{
	char	*home;
	char	*next_pwd;
	char	*actual_pwd;

	home = get_value_from_key(data->ppt->list, "HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return ;
	}
	if (chdir(home) != 0)
	{
		perror("chdir");
		free (home);
		return ;
	}
	actual_pwd = get_value_from_key(data->ppt->list, "PWD");
	modify_value(data, "OLDPWD", &actual_pwd);
	modify_value(data, "PWD", &next_pwd);
}

static void	do_cd(t_msh *data)
{
	char	*next_pwd;
	char	*actual_pwd;

	next_pwd = do_dot(data);
	if (abs_string_cmp(next_pwd, "-"))
	{
		go_back(data, &next_pwd);
		return ;
	}
	if (chdir(next_pwd) != 0)
	{
		perror("chdir");
		free (next_pwd);
		return ;
	}
	actual_pwd = get_value_from_key(data->ppt->list, "PWD");
	modify_value(data, "OLDPWD", &actual_pwd);
	modify_value(data, "PWD", &next_pwd);
}

void	builtin_cd(t_msh *data)
{
	int		n_cmd;
	char	*cmd;

	n_cmd = 0;
	while (data->lst_cmd->argv[n_cmd])
		n_cmd++;
	if (n_cmd > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return ;
	}
	if (n_cmd == 1)
		go_home(data);
	if (n_cmd == 2)
	{
		cmd = data->lst_cmd->argv[1];
		if (abs_string_cmp(cmd, "~"))
			go_home(data);
		do_cd(data);
	}
	free_table(data->env);
	init_env_table(data);
}
