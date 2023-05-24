/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:11:46 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/05/22 22:12:08 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"


int jump_sq_exp(char *str, int i, char **newstr, int *newi)
{
	int	j;

	j = i;
	if (str[j] == '\'')
	{
		while (str[j])
		{
			(*newstr)[*newi] = str[j];
			(*newi)++;
			str++;
			i++;
			if (str[j] == '\'')
			{
				(*newstr)[*newi] = str[j];
				(*newi)++;
				return (i + 1);
			}
		}
	}
	return (i);
}


int jump_sq(char *str, int i)
{
	int	j;

	j = i;
	if (str[j] == '\'')
	{
		while (str[j])
		{
			str++;
			i++;
			if (str[j] == '\'')
				return (i);
		}
	}
	return (i);
}

/*	$fabio=10
	      01234567890
	str = valli$fabio$kelvin > is_key_in_env
	vai ate '$' ||  || '\"' || '\''
	se encontrar '\'', pula ate o proximo '\''
	get_value_from_key
	strlen(value)
	newstr = malloc
	anda str e copia str para newstr
	free(str)
	result = valli10*/

static int	get_len_move_i(t_msh *data, char *str, int *begin)
{
	int		len;
	int		end;
	char	*tmp;
	char	*value;

	end = *begin;
	while (str[end] != '\0' && str[end] != '$' && str[end] != '\'' && str[end] != '\"')
	{
		end++;
//		(*begin)++;
	}
	tmp = ft_substr(str, *begin, (end - *begin));
	value = get_value_from_key(data->export->env, tmp);
	if (value)
	{
		len = ft_strlen(value);
		free(tmp);
		free (value);
		*begin = end;
		return (len);
	}
	*begin = end;
	return (0);
}

static int	get_true_len(t_msh *data, char *str)
{
	int		i;
	int		len_total;

	i = 0;
	len_total = 0;
	while (str[i])
	{
		i = jump_sq(str, i);
		if (str[i] == '$')
		{
			i++;
			len_total += get_len_move_i(data, str, &i);
		}
		else
		{
			len_total++;
			i++;
		}
	}
	return (len_total);
}

static void	expand_word_lstarg(t_msh *data, char *word)
{
	int		begin;
	int		end;
	char	*str;
	char	*newstr;
	char	*tmpstr;
	char	*value;
	int		i;
	int 	newi;


	newi = 0;
	begin = -1;
	str = word;
	newstr = (char *)malloc(sizeof(char) * (get_true_len(data, str) + 1));
	while (str[++begin])
	{
		begin = jump_sq_exp(str, begin, &newstr, &newi);
		if (str[begin] == '$' && str[begin + 1])
		{
			end = begin + 1;
			while (str[end]  != '\0' && str[end] != '$' && str[end] != '\'' && str[end] != '\"')
				end++;
			tmpstr = ft_substr(str, begin + 1, (end - 1 - begin));
			value = get_value_from_key(data->export->env, tmpstr);
			if (value)
			{
				i = 0;
				while (value[i])
				{
					newstr[newi] = value[i];
					begin++;
					i++;
					newi++;
				}
			}
			begin = end - 1;
			free(value);
			free(tmpstr);
		}
		else
		{
			newstr[newi] = str[begin];
			newi++;
		}
	}
	newstr[newi] = '\0';
	if (*newstr == '\0')
	{
		free(newstr);
		data->lst_cmd->lstarg->content = NULL;
	}
	else
	{
		free(data->lst_cmd->lstarg->content);
		data->lst_cmd->lstarg->content = newstr;
	}
}

static void	expand_word_lstRedOut(t_msh *data, char *word)
{
	int		begin;
	int		end;
	char	*str;
	char	*newstr;
	char	*tmpstr;
	char	*value;
	t_redir	*temp;
	int		i;
	int 	newi;

	newi = 0;
	begin = -1;
	temp = (t_redir *)data->lst_cmd->lstofredirout->content;
	str = word;
	newstr = (char *)malloc(sizeof(char) * (get_true_len(data, str) + 1));
	while (str[++begin])
	{
		begin = jump_sq_exp(str, begin, &newstr, &newi);
		if (str[begin] == '$' && str[begin + 1])
		{
			end = begin + 1;
			while (str[end]  != '\0' && str[end] != '$' && str[end] != '\'' && str[end] != '\"')
				end++;
			tmpstr = ft_substr(str, begin + 1, (end - 1 - begin));
			value = get_value_from_key(data->export->env, tmpstr);
			if (value)
			{
				i = 0;
				while (value[i])
				{
					newstr[newi] = value[i];
					begin++;
					i++;
					newi++;
				}
			}
			begin = end - 1;
			free(value);
			free(tmpstr);
		}
		else
		{
			newstr[newi] = str[begin];
			newi++;
		}
	}
	newstr[newi] = '\0';
	if (*newstr == '\0')
	{
		free(newstr);
		temp->filename = NULL;
	}
	else
	{
		free(temp->filename);
		temp->filename = newstr;
	}
}

static void	expand_word_lstRedIn(t_msh *data, char *word)
{
	int		begin;
	int		end;
	char	*str;
	char	*newstr;
	char	*tmpstr;
	char	*value;
	t_redir	*temp;
	int		i;
	int 	newi;

	newi = 0;
	begin = -1;
	temp = (t_redir *)data->lst_cmd->lstofredirin->content;
	str = word;
	newstr = (char *)malloc(sizeof(char) * (get_true_len(data, str) + 1));
	while (str[++begin])
	{
		begin = jump_sq_exp(str, begin, &newstr, &newi);
		if (str[begin] == '$' && str[begin + 1])
		{
			end = begin + 1;
			while (str[end]  != '\0' && str[end] != '$' && str[end] != '\'' && str[end] != '\"')
				end++;
			tmpstr = ft_substr(str, begin + 1, (end - 1 - begin));
			value = get_value_from_key(data->export->env, tmpstr);
			if (value)
			{
				i = 0;
				while (value[i])
				{
					newstr[newi] = value[i];
					begin++;
					i++;
					newi++;
				}
			}
			begin = end - 1;
			free(value);
			free(tmpstr);
		}
		else
		{
			newstr[newi] = str[begin];
			newi++;
		}
	}
	newstr[newi] = '\0';
	if (*newstr == '\0')
	{
		free(newstr);
		temp->filename = NULL;
	}
	else
	{
		free(temp->filename);
		temp->filename = newstr;
	}
}


void expander(t_msh *data)
{
	t_scom	*lst;
	t_list	*tmp;
	t_redir	*temp;
//	char	*word;
	int		i;

	i = 0;
	lst = data->lst_cmd;
	while (data->lst_cmd)
	{
		tmp = data->lst_cmd->lstarg;
		while(data->lst_cmd->lstarg)
		{
			expand_word_lstarg(data, data->lst_cmd->lstarg->content);
			data->lst_cmd->lstarg = data->lst_cmd->lstarg->next;
		}
		data->lst_cmd->lstarg = tmp;

		tmp = data->lst_cmd->lstofredirout;
		while(data->lst_cmd->lstofredirout)
		{
			temp = (t_redir *)(data->lst_cmd->lstofredirout->content);
			expand_word_lstRedOut(data, temp->filename);
			data->lst_cmd->lstofredirout = data->lst_cmd->lstofredirout->next;
		}
		data->lst_cmd->lstofredirout = tmp;

		tmp = data->lst_cmd->lstofredirin;
		while(data->lst_cmd->lstofredirin)
		{
			temp = (t_redir *)(data->lst_cmd->lstofredirin->content);
			if (temp->type == LESS)
			{
				expand_word_lstRedIn(data, temp->filename);
			}
			data->lst_cmd->lstofredirin = data->lst_cmd->lstofredirin->next;
		}
		data->lst_cmd->lstofredirin = tmp;
		i++;
		data->lst_cmd = data->lst_cmd->next;
	}
	data->lst_cmd = lst;
}
