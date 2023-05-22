/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 10:26:35 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/22 14:19:55 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	free_print_exit(t_msh *data, char *s, int fd, char *f)
{
	int	flag;

	flag = ft_atoi(f);
	free_all(data);
	ft_putstr_fd(s, fd);
	exit ((unsigned char)flag);
}

void	builtin_exit(t_msh *data)
{
	char	**arg;

	arg = data->lst_cmd->argv;
	if (arg[0] && arg[1] == NULL)
		free_print_exit(data, "exit\n", 1, "0");
	if (!ptr_is_digit(arg[1]))
		free_print_exit(data, "msh: exit: numeric argument required\n", 2, "2");
	if (ptr_is_digit(arg[1]) && arg[2] == NULL)
		free_print_exit(data, "exit\n", 1, arg[1]);
	if (ptr_is_digit(arg[1]) && arg[2] != NULL)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many argument\n", 2);
		return ;
	}
}

void	builtin_exit_update(t_msh *data)
{
	char	**arg;

	arg = data->lst_cmd->argv;
	if (arg[0] && arg[1] == NULL)
		free_print_exit(data, "exit\n", 1, "0");
	if (!ptr_is_digit(arg[1]))
		free_print_exit(data, "msh: exit: numeric argument required\n", 2, "2");
	if (ptr_is_digit(arg[1]) && arg[2] == NULL)
		free_print_exit(data, "exit\n", 1, arg[1]);
	if (ptr_is_digit(arg[1]) && arg[2] != NULL)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many argument\n", 2);
		return ;
	}
}
