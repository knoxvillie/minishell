/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exptoenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:48:39 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/29 09:41:53 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_unset(t_msh *data, char *key)
{
	if (check_exp_first_node(data, key))
		return ;
	if (check_exp_till_end(data, key))
		return ;
}
