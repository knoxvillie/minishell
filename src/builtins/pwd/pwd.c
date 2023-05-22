/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:31:15 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/22 14:17:40 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	builtin_pwd(t_msh *data)
{
	if (data->lst_cmd->argv[1])
	{
		ft_putstr_fd("msh: pwd: too many arguments\n", 2);
		return ;
	}
	ft_putstr_fd(data->ppt->abs_path, 1);
	ft_putstr_fd("\n", 1);
}
