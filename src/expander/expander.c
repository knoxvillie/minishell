/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:11:46 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/05/27 17:59:21 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

void	check_expander(t_msh *data, void **content)
{
	int		i;
	char	quote;
	char	*arg;
	char	*expanded;

	if (full_dolar((char *)(*content)))
		return ;
	i = -1;
	quote = '\0';
	arg = (char *)(*content);
	data->num = 0;
	expanded = (char *)malloc(sizeof(char) * (size_expand(data, arg) + 1));
	while (arg[++i])
	{
		quote = quote_value(arg[i], quote);
		if (arg[i] == '$' && quote != '\'')
			do_expander(data, arg, &expanded, &i);
		else
			expanded[data->num++] = arg[i];
	}
	expanded[data->num] = '\0';
	free (*content);
	*content = expanded;
}

static void	do_expand_lstarg(t_msh *data)
{
	t_list	*tmp;

	tmp = data->lst_cmd->lstarg;
	while (tmp)
	{
		if (ft_strrchr((char *)tmp->content, '$'))
			check_expander(data, &tmp->content);
		tmp = tmp->next;
	}
}

static void	do_expand_redout(t_msh *data)
{
	t_list	*tmp;
	t_redir	*tmpred;

	tmp = data->lst_cmd->lstofredirout;
	while (tmp)
	{
		tmpred = (t_redir *)(tmp->content);
		if (ft_strrchr(tmpred->filename, '$'))
			check_expander(data, (void **)(&tmpred->filename));
		tmp = tmp->next;
	}
}

static void	do_expand_redin(t_msh *data)
{
	t_list	*tmp;
	t_redir	*tmpred;

	tmp = data->lst_cmd->lstofredirin;
	while (tmp)
	{
		tmpred = (t_redir *)(tmp->content);
		if (ft_strrchr(tmpred->filename, '$') && tmpred->type == LESS)
			check_expander(data, (void **)(&tmpred->filename));
		tmp = tmp->next;
	}
}

void	expander(t_msh *data)
{
	t_scom	*tmp;

	tmp = data->lst_cmd;
	while (tmp)
	{
		do_expand_lstarg(data);
		do_expand_redout(data);
		do_expand_redin(data);
		tmp = tmp->next;
	}
}
