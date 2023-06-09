/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:24:35 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/27 19:06:53 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	builtin_env(t_msh *data)
{
	t_env	*node;

	node = data->ppt->list;
	while (node)
	{
		ft_putstr_fd(node->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(node->value, 1);
		ft_putstr_fd("\n", 1);
		node = node->next;
	}
	g_exit_status = 0;
}
