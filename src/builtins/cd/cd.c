/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 10:47:40 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/24 10:44:04 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	do_cd(t_msh *data);

static void	go_back(t_msh *data)
{
	char	*next_pwd;
	char	*actual_pwd;

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
	char	*actual_pwd;

	home = get_value_from_key(data->ppt->list, "HOME");
	if (!home)
		return (free (home), ft_putstr_fd("msh: HOME not set\n", 2));
	if (chdir(home) != 0)
	{
		perror("chdir");
		free (home);
		return ;
	}
	actual_pwd = get_value_from_key(data->ppt->list, "PWD");
	modify_value(data, "OLDPWD", &actual_pwd);
	modify_value(data, "PWD", &home);
}

static void	do_cd(t_msh *data)
{
	char	*next_pwd;
	char	*actual_pwd;

	next_pwd = ft_strdup(data->lst_cmd->argv[1]);
	if (abs_string_cmp(next_pwd, "-"))
		return (free (next_pwd), go_back(data));
	if (abs_string_cmp(next_pwd, "~"))
		return (free (next_pwd), go_home(data));
	if (chdir(next_pwd) != 0)
	{
		perror("chdir");
		free (next_pwd);
		return ;
	}
	free (next_pwd);
	next_pwd = getcwd(NULL, 0);
	actual_pwd = get_value_from_key(data->ppt->list, "PWD");
	modify_value(data, "OLDPWD", &actual_pwd);
	modify_value(data, "PWD", &next_pwd);
}

void	builtin_cd(t_msh *data)
{
	int	number_cmds;

	number_cmds = 0;
	while (data->lst_cmd->argv[number_cmds])
		number_cmds++;
	if (number_cmds > 2)
		return (ft_putstr_fd("msh: cd: too many arguments\n", 2));
	if (number_cmds == 1)
		go_home(data);
	if (number_cmds == 2)
		do_cd(data);
	free_table(data->env);
	init_env_table(data);
}
