/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:28:16 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/27 18:28:16 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

bool	check_unclosed_quotes(char *input)
{
	char	inside_q;

	inside_q = '\0';
	while (*input)
	{
		while (*input && !inside_q)
		{
			if (*input == '\'' || *input == '\"')
				inside_q = *input;
			input++;
		}
		while (*input && inside_q)
		{
			if (*input == inside_q)
				inside_q = '\0';
			input++;
		}
	}
	if (!inside_q)
		return (true);
	return (false);
}

t_scom	*ft_lstlastscom(t_scom *lst)
{
	t_scom	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

t_scom	*ft_lstnewscom(void)
{
	t_scom	*new_node;

	new_node = (t_scom *)malloc(sizeof(t_scom));
	if (!new_node)
		return (NULL);
	new_node->i = 0;
	new_node->next = NULL;
	new_node->lstarg = NULL;
	new_node->argv = NULL;
	new_node->lstofredirin = NULL;
	new_node->lstofredirout = NULL;
	new_node->ft_stdin = STDIN_FILENO;
	new_node->ft_stdout = STDOUT_FILENO;
	return (new_node);
}

void	ft_lstadd_backscom(t_scom **lst, t_scom *new)
{
	t_scom	*temp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = ft_lstlastscom(*lst);
		temp->next = new;
	}
}

void	free_lst(t_scom *lst)
{
	t_list	*next;

	if (lst->lstarg == NULL)
		return ;
	while (lst->lstarg)
	{
		next = lst->lstarg->next;
		if (lst->lstarg->content)
			free(lst->lstarg->content);
		free(lst->lstarg);
		lst->lstarg = next;
	}
}
