/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:20:55 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/15 12:04:34 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	check_flag(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' && arg[i + 1] != 'n')
		return (false);
	while (arg[i])
	{
		if (arg[i] == '-' && i == 0)
		{
			i++;
			while (arg[i] == 'n')
				i++;
			if (arg[i] == '\0')
				return (true);
			break ;
		}
		i++;
	}
	return (false);
}

static void	do_echo(char **arg, int pos)
{
	int		i;
	char	*str;
	char	delimiter;

	while (arg[pos])
	{
		i = -1;
		delimiter = '\0';
		str = arg[pos];
		while (str[++i])
		{
			if (str[i] == delimiter)
				continue ;
			if (str[i] == '\\')
				continue ;
			if (str[i] == '\'' || str[i] == '\"')
			{
				if (i == 0)
				{
					delimiter = str[i];
					continue ;
				}
				if (delimiter == '\0')
				{
					delimiter = str[i];
					continue ;
				}
			}
			ft_putchar_fd(str[i], 1);
		}
		if (arg[++pos] != NULL)
			ft_putchar_fd(' ', 1);
	}
}

void	builtins_echo(t_msh *data)
{
	char	**arg;
	int		i;

	arg = data->lst_cmd->argv;
	i = 1;
	while (check_flag(arg[i]))
		i++;
	if (arg[i] == NULL)
		return ;
	do_echo(arg, i);
	if (i == 1)
		ft_putchar_fd('\n', 1);
}
