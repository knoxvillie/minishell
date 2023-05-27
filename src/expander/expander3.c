/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:22:30 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/27 18:22:30 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

void	size_expand_2(t_msh *data, char *arg, int *i, int *len)
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
		if (j == 0)
			value = ft_strdup("$");
		if (value)
			*len += (int)ft_strlen(value);
		free(key);
		free (value);
		*i += j;
	}
	else
		size_expand_2_aux(len, i);
}

int	size_expand(t_msh *data, char *arg)
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

void	expand_exit_status(t_msh *data, char **ppt, int *i)
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

void	do_expander_if(t_msh *data, char *value, char **ptr)
{
	int	k;

	if (value)
	{
		k = -1;
		while (value[++k])
			(*ptr)[data->num++] = value[k];
		free (value);
	}
}

void	do_expander(t_msh *data, char *arg, char **ptr, int *i)
{
	char	*key;
	char	*value;
	int		len;

	if (arg[*i + 1] != '?')
	{
		len = 0;
		while (is_alnumunder(arg[*i + 1 + len]))
			len++;
		key = ft_substr(arg, *i + 1, len);
		value = get_value_from_key(data->ppt->list, key);
		if (len == 0)
			value = ft_strdup("$");
		free(key);
		*i += len;
		do_expander_if(data, value, ptr);
	}
	else
		expand_exit_status(data, ptr, i);
}
