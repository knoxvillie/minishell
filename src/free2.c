/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:33:28 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/27 17:04:30 by kfaustin         ###   ########.fr       */
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

void	close_pipes(t_msh *data)
{
	int	i;

	if (data->npipe == 0)
		return ;
	i = 0;
	while (i < data->npipe)
	{
		close(data->fd[i][0]);
		close(data->fd[i][1]);
		i++;
	}
}

void	free_fd(t_msh *data)
{
	int	i;

	i = 0;
	if (data->fd == NULL)
		return ;
	while (i < data->npipe)
	{
		free(data->fd[i]);
		i++;
	}
	free(data->fd);
	data->fd = NULL;
}

void	free_t_exp(t_env *list)
{
	t_env	*env;

	if (list == NULL)
		return ;
	while (list)
	{
		free(list->key);
		if (list->value != NULL)
			free (list->value);
		env = list->next;
		free(list);
		list = env;
	}
}
