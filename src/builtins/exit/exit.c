/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 10:26:35 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/24 12:54:16 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	free_print_exit(t_msh *data, char *msg, int fd, char *value_txt)
{
	g_exit_status = ft_atoi(value_txt);
	ft_putstr_fd("exit\n", fd);
	ft_putstr_fd(msg, fd);
	free_all(data);
	exit ((unsigned char)g_exit_status);
}

void	builtin_exit(t_msh *data)
{
	char	**arg;

	arg = data->lst_cmd->argv;
	if (arg[1] == NULL)
		free_print_exit(data, NULL, 1, "0");
	if (!ptr_is_digit(arg[1]))
		free_print_exit(data, "msh: exit: numeric argument required\n", 2, "2");
	if (ptr_is_digit(arg[1]) && arg[2] == NULL)
		free_print_exit(data, NULL, 1, arg[1]);
	if (ptr_is_digit(arg[1]) && arg[2] != NULL)
	{
		g_exit_status = 1;
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("msh: exit: too many argument\n", 2);
		return ;
	}
}

static void	free_exit(t_msh *data, char *value_txt)
{
	g_exit_status = ft_atoi(value_txt);
	free_all(data);
	exit ((unsigned char)g_exit_status);
}

void	builtin_exit_update(t_msh *data)
{
	char	**arg;

	arg = data->lst_cmd->argv;
	if (arg[0] && arg[1] == NULL)
		free_exit(data, "0");
	if (!ptr_is_digit(arg[1]))
		free_exit(data, "2");
	if (ptr_is_digit(arg[1]) && arg[2] == NULL)
		free_exit(data, arg[1]);
	if (ptr_is_digit(arg[1]) && arg[2] != NULL)
	{
		g_exit_status = 1;
		return ;
	}
}
