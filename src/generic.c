/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:12:39 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/18 14:29:15 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	put_str_exit(char *str, int flag)
{
	ft_putstr_fd(str, 2);
	exit(flag);
}

bool	abs_string_cmp(char *s1, char *s2)
{
	int		len_s1;
	int		len_s2;

	len_s1 = (int)ft_strlen(s1);
	len_s2 = (int) ft_strlen(s2);
	if ((len_s1 == len_s2) && !ft_strncmp(s1, s2, len_s1))
		return (true);
	return (false);
}

int	size_of_list(t_env *lst)
{
	int		size;
	t_env	*tmp;

	size = 0;
	tmp = lst;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

bool	ptr_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-' && i == 0)
			i++;
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}
