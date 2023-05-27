/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:31:54 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/27 18:36:41 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

int	jump_dq_and_sq(char **str, int i)
{
	if (**str == '\"')
	{
		while (**str)
		{
			(*str)++;
			i++;
			if (**str == '\"')
				return (i);
		}
	}
	else if (**str == '\'')
	{
		while (**str)
		{
			(*str)++;
			i++;
			if (**str == '\'')
				return (i);
		}
	}
	return (i);
}

int	get_token_aux(t_redir *red, t_scom *scom, char **str, int type)
{
	int	i;

	i = 0;
	while (**str && !ft_strchr(WSPACE, **str)
		&& !ft_strchr(METACH, **str) && !ft_strchr(UNSUPMETACH, **str))
	{
		i = jump_dq_and_sq(str, i);
		(*str)++;
		i++;
	}
	red->filename[i] = '\0';
	if (type == GREATGREAT || type == GREAT)
		return (ft_lstadd_back(&(scom->lstofredirout), ft_lstnew(red)), 0);
	else
		return (ft_lstadd_back(&(scom->lstofredirin), ft_lstnew(red)), 0);
}

int	get_token_word_redir(t_msh	*data, char **str, int type)
{
	t_scom	*scom;
	t_redir	*red;

	red = (t_redir *)malloc(sizeof(t_redir));
	red->type = type;
	scom = ft_lstlastscom(data->lst_cmd);
	while (**str && ft_strchr(WSPACE, **str))
		(*str)++;
	if (**str && (ft_strchr(METACH, **str) || ft_strchr(UNSUPMETACH, **str)))
	{
		ft_putstr_fd("\"syntax error near unxp token `", 2);
		ft_putchar_fd(**str, 2);
		ft_putstr_fd("\'\n", 2);
		return (free(red), 1);
	}
	if (**str == '\0')
	{
		ft_putstr_fd("syntax error near unxp token `newline\'\n", 2);
		return (free(red), 1);
	}
	red->filename = ft_strdup(*str);
	return (get_token_aux(red, scom, str, type));
}

int	redirout(t_msh	*data, char **str)
{
	(*str)++;
	if (**str == '>')
		return ((*str)++, get_token_word_redir(data, str, GREATGREAT));
	else
		return (get_token_word_redir(data, str, GREAT));
}

int	redirin(t_msh	*data, char **str)
{
	(*str)++;
	if (**str == '<')
	{
		data->heredoc = 1;
		return ((*str)++, get_token_word_redir(data, str, LESSLESS));
	}
	else
		return (get_token_word_redir(data, str, LESS));
}
