/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:25:58 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/27 18:10:19 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

int	get_token(t_msh	*data, char **str)
{
	while (**str && ft_strchr(WSPACE, **str))
		(*str)++;
	if (**str == '|')
		return (get_token_pipe(data, str));
	else if (**str == '<')
		return (redirin(data, str));
	else if (**str == '>')
		return (redirout(data, str));
	else if (**str && ft_strchr(UNSUPMETACH, **str))
		return (printf("Msh does not sup this op. %c\n", **str), (*str)++, 1);
	else
		get_token_word(data, str);
	return (0);
}

int	size_lstarg(t_scom *data)
{
	int		i;
	t_list	*tmp;

	tmp = data->lstarg;
	if (!tmp)
		return (0);
	i = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	init_argv_norm(t_msh *data, int nscom)
{
	data->nscom = nscom;
	data->npipe = nscom - 1;
}

void	init_argv(t_msh *data)
{
	int		i;
	int		nscom;
	t_list	*tmparglst;
	t_scom	*tmpscom;

	tmpscom = data->lst_cmd;
	nscom = 0;
	while (tmpscom != NULL)
	{
		i = size_lstarg(tmpscom);
		tmparglst = tmpscom->lstarg;
		tmpscom->i = nscom;
		tmpscom->argv = (char **)malloc(sizeof(char *) * (i + 1));
		i = 0;
		while (tmparglst != NULL)
		{
			if (tmparglst->content)
				tmpscom->argv[i++] = ft_strdup((char *)tmparglst->content);
			tmparglst = tmparglst->next;
		}
		tmpscom->argv[i] = NULL;
		nscom++;
		tmpscom = tmpscom->next;
	}
	init_argv_norm(data, nscom);
}

int	ft_parse(char *input, t_msh *data)
{
	char	*str;
	t_scom	*tmp;

	str = input;
	tmp = ft_lstnewscom();
	ft_lstadd_backscom(&(data->lst_cmd), tmp);
	if (!check_unclosed_quotes(input))
	{
		ft_putstr_fd("Error: Unclosed quotes found\n", 2);
		return (1);
	}
	while (*str)
	{
		if (get_token(data, &str))
			return (1);
	}
	if (check_nbr_pipes(data->lst_cmd))
		return (1);
	expander(data);
	init_argv(data);
	data->pid = (pid_t *)malloc(sizeof(pid_t) * data->nscom);
	return (0);
}
