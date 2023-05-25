/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:11:46 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/05/26 00:36:33 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"



static char	quote_value(char c, char quote)
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

static void	size_expand_2(t_msh *data, char *arg, int *i, int *len)
{
	int		j;
	char	*key;
	char	*value;

	j = 0;
	if (arg[*i + 1] != '?')
	{
		while (is_alnumunder(arg[*i + 1 + j]))
			j++;
		key = ft_substr(arg, *i + 1, j);
		value = get_value_from_key(data->ppt->list, key);
		if (value == NULL)
			value = ft_strdup("$");
		*len += (int)ft_strlen(value);
		free(key);
		free (value);
		*i += j;
	}
	else
	{
		key = ft_itoa(g_exit_status);
		*len += (int)ft_strlen(key);
		free(key);
		*i += 1;
	}
}

static int	size_expand(t_msh *data, char *arg)
{
	int		i;
	int		len;
	char	quote;

	i = -1;
	len = 0;
	quote = '\0';
	while (arg && arg[++i])
	{
		quote = quote_value(arg[i], quote);
		if (arg[i] == '$' && quote != '\'')
			size_expand_2(data, arg, &i, &len);
		else
			len++;
	}
	return (len);
}

static void	expand_exit_status(t_msh *data, char **ppt, int *i)
{
	int		k;
	char	*value;

	value = ft_itoa(g_exit_status);
	k = -1;
	while (value[++k])
		(*ppt)[data->num++] = value[k];
	free(value);
	*i += 1;
}

static void	do_expander(t_msh *data, char *arg, char **ptr, int *i)
{
	char	*key;
	char	*value;
	int		len;
	int		k;

	if (arg[*i + 1] != '?')
	{
		len = 0;
		while (is_alnumunder(arg[*i + 1 + len]))
			len++;
		key = ft_substr(arg, *i + 1, len);
		value = get_value_from_key(data->ppt->list, key);
		if (value == NULL)
			value = ft_strdup("$");
		free(key);
		*i += len;
		k = -1;
		while (value[++k])
			(*ptr)[data->num++] = value[k];
		free (value);
	}
	else
		expand_exit_status(data, ptr, i);
}

static void	check_expander(t_msh *data, void **content)
{
	int		i;
	char	quote;
	char	*arg;
	char	*expanded;

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
	while(tmp)
	{
		if (ft_strrchr((char *)tmp->content, '$'))
			check_expander(data, &tmp->content);
		tmp = tmp->next;
	}
}
static void	do_expand_redOut(t_msh *data)
{
	t_list	*tmp;
	t_redir	*tmpRed;

	tmp = data->lst_cmd->lstofredirout;
	while(tmp)
	{
		tmpRed = (t_redir *)(tmp->content);
		if (ft_strrchr(tmpRed->filename, '$'))
			check_expander(data, (void **)(&tmpRed->filename));
		tmp = tmp->next;
	}
}

static void	do_expand_redIn(t_msh *data)
{
	t_list	*tmp;
	t_redir	*tmpRed;

	tmp = data->lst_cmd->lstofredirin;
	while(tmp)
	{
		tmpRed = (t_redir *)(tmp->content);
		if (ft_strrchr(tmpRed->filename, '$') && tmpRed->type == LESS)
			check_expander(data, (void **)(&tmpRed->filename));
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
		do_expand_redOut(data);
		do_expand_redIn(data);
		tmp = tmp->next;
	}
}
