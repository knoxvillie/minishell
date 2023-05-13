/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 10:47:40 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/13 13:16:40 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	do_cd(t_msh *data)
{
	char	*next_pwd;
	char	**actual_pwd;
	char	**old_pwd;

	next_pwd = ft_strdup(data->lst_cmd->argv[1]);
	if (chdir(next_pwd) != 0)
	{
		perror("chdir");
		return (false);
	}
	actual_pwd = (char **)
	actual_pwd = get_value_from_key(data->ppt->list, "PWD");
	modify_value(data, "OLDPWD", actual_pwd);
	modify_value(data, "PWD", next_pwd);
	return (true);
}

void	builtin_cd(t_msh *data)
{
	int	n_cmd;

	n_cmd = 0;
	while (data->lst_cmd->argList[n_cmd])
		n_cmd++;
	if (n_cmd > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return ;
	}
	if (n_cmd == 1)
			;
	if (n_cmd == 2)
}