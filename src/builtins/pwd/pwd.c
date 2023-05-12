/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:31:15 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/11 15:40:09 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	builtin_pwd(t_msh *data)
{

	if (data->lst_cmd->argList[1])
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return ;
	}
	ft_putstr_fd(data->ppt->abs_path, 1);
	ft_putstr_fd("\n", 1);
}