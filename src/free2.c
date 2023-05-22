/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:33:28 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/22 14:36:25 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_t_env(t_env *list)
{
	t_env	*header;

	while (list)
	{
		header = list->next;
		free (list->key);
		free (list->value);
		free (list);
		list = header;
	}
}

void	free_fd(t_msh *data)
{
	int	i;

	i = 0;
	while (i < data->npipe)
	{
		free(data->fd[i]);
		i++;
	}
	free(data->fd);
}
