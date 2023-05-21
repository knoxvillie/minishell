/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 10:47:40 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/16 11:24:37 by kfaustin         ###   ########.fr       */
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

	home = get_value_from_key(data->ppt->list, "HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return ;
	}
	do_cd(data, &home);
}

static void	do_cd(t_msh *data, char	**var_home)
{
	char	*next_pwd;
	char	*actual_pwd;

	if (!var_home)
	{
		next_pwd = ft_strdup(data->lst_cmd->argv[1]);
		if (!ft_strncmp(next_pwd, "-", 1))
		{
			go_back(data, &next_pwd);
			return ;
		}
	}
	else
		next_pwd = *var_home;
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
	int	n_cmd;

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
		do_cd(data, NULL);
	free_table(data->env);
	init_env_table(data);
}
