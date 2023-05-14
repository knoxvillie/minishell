/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 10:26:35 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/13 10:26:35 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"



//Supostamente o exit retorna unsiged char, 0-255.
int	builtin_exit(t_msh *data)
{
	int		n_cmd;

	n_cmd = 0;
	while (data->lst_cmd->argv[n_cmd])
		n_cmd++;
	if (n_cmd > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (-1);
	}
	if (n_cmd == 1)
	{
		free_all(data);
		return (0);
	}
	if (n_cmd == 2)
}
