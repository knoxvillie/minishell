/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:22:34 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/05/18 15:21:36 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
==357880== 0 bytes in 1 blocks are definitely lost in loss record 1 of 62
==357880==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==357880==    by 0x401302: create_pipe (create_pipe.c:20)
==357880==    by 0x401CA2: do_minishell (main.c:43)
==357880==    by 0x401BDE: main (main.c:63)
*/

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