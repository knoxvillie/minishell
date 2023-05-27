/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:20:53 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/27 18:26:32 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

bool	full_dolar(const char *arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
	{
		if (arg[i] != '$')
			return (false);
		i++;
	}
	return (true);
}

char	quote_value(char c, char quote)
{
	if (ft_strrchr("\"\'", c) && !quote)
		return (c);
	else if (ft_strrchr("\"\'", c) && quote == c)
		return (0);
	return (quote);
}

int	is_alnumunder(int c)
{
	if (ft_isalpha(c) == 1 || ft_isdigit(c) == 1 || c == '_')
		return (1);
	else
		return (0);
}

void	size_expand_2_aux(int *len, int *i)
{
	char	*key;

	key = ft_itoa(g_exit_status);
	*len += (int)ft_strlen(key);
	*i += 1;
	free(key);
}
