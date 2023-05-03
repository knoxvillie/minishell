/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:50:56 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/03 10:50:56 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	check_syntax(char *str)
{
	char	**table;
	int		i;

	i = -1;
	while (str[++i])
	{
		if ()
	}
}

// str must be handled before the func to prevent unclosed quotes: ARG='kelvin"
void	builtin_export(t_env *header, char *str)
{
	char	**table;

	table = ft_split(str, '=');

}