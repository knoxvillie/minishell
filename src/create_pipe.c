/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:22:34 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/05/14 19:57:04 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by fvalli-v on 14-05-2023.
//

#include "../includes/minishell.h"

void	create_pipe(t_msh *data)
{
	int	i;

	i = 0;
	data->fd = (int **)malloc(sizeof(int *) * data->npipe);
	if (!data->fd)
	{
		ft_putstr_fd("Error while trying to malloc.\n", STDERR_FILENO);
		exit(1);
	}
	while (i < data->npipe)
	{
		data->fd[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe(data->fd[i]) < 0)
		{
			ft_putstr_fd("Error while opening pipes\n", STDERR_FILENO);
			exit(1);
		}
		i++;
	}
}