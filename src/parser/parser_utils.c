/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:39:42 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/27 18:19:32 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by fvalli-v on 07-05-2023.
//

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

int	get_token_pipe(t_msh *data, char **str)
{
	(*str)++;
	if (**str == '|')
		return (printf("Minishell does not support this operator \'||\'\n"), 1);
	else
	{
		while (**str && ft_strchr(WSPACE, **str))
			(*str)++;
		if (**str == '|')
		{
			printf("syntax error near unexpected token `%c\'\n",**str);
			return (1);
		}
	}
	return (ft_lstadd_backscom(&(data->lst_cmd), ft_lstnewscom()), 0);
}

void	get_token_word(t_msh *data, char **str)
{
	char	*tmp;
	int		i;
	t_scom	*scom;

	scom = ft_lstlastscom(data->lst_cmd);
	tmp = ft_strdup(*str);
	i = 0;
	while (**str && !ft_strchr(WSPACE, **str) && !ft_strchr(METACH, **str))
	{
		i = jump_dq_and_sq(str, i);
		(*str)++;
		i++;
	}
	tmp[i] = '\0';
	if (i != 0)
		ft_lstadd_back(&(scom->lstarg), ft_lstnew(tmp));
}
