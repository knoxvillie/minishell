/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:20:55 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/22 14:17:08 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	check_flag(char *arg)
{
	int	i;

	if (!arg)
		return (false);
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

static bool	check_delimiter(char *str, char xar, char *del, int pos)
{
	if (xar == *del && pos != 0 && str[pos - 1] != '\\')
	{
		*del = '\0';
		return (true);
	}
	if (xar == '\\')
		return (true);
	if ((xar == '\'' || xar == '\"') && *del == '\0')
	{
		if (pos == 0)
		{
			*del = xar;
			return (true);
		}
		if (str[pos - 1] == '\\')
		{
			ft_putchar_fd(xar, 1);
			return (true);
		}
		*del = xar;
		return (true);
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
		str = arg[pos];
		delimiter = '\0';
		while (str[++i])
		{
			if (check_delimiter(str, str[i], &delimiter, i))
				continue ;
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
