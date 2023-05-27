/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:31:54 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/27 18:31:54 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

void	free_lst_redirin(t_scom *lst)
{
	t_list	*next;
	t_redir	*tmp;

	if (lst->lstofredirin == NULL)
		return ;
	while (lst->lstofredirin)
	{
		next = lst->lstofredirin->next;
		if (lst->lstofredirin->content)
		{
			tmp = lst->lstofredirin->content;
			free(tmp->filename);
			free(lst->lstofredirin->content);
		}
		free(lst->lstofredirin);
		lst->lstofredirin = next;
	}
}

void	free_lst_redirout(t_scom *lst)
{
	t_list	*next;
	t_redir	*tmp;

	if (lst->lstofredirout == NULL)
		return ;
	while (lst->lstofredirout)
	{
		next = lst->lstofredirout->next;
		if (lst->lstofredirout->content)
		{
			tmp = lst->lstofredirout->content;
			free(tmp->filename);
			free(lst->lstofredirout->content);
		}
		free(lst->lstofredirout);
		lst->lstofredirout = next;
	}
}

void	free_lstscom(t_msh *data)
{
	t_scom	*next;

	if (data->lst_cmd == NULL)
		return ;
	while (data->lst_cmd)
	{
		next = data->lst_cmd->next;
		free_table(data->lst_cmd->argv);
		free_lst(data->lst_cmd);
		free_lst_redirin(data->lst_cmd);
		free_lst_redirout(data->lst_cmd);
		free(data->lst_cmd);
		data->lst_cmd = next;
	}
}

int	check_node_empty(t_scom *lst)
{
	t_scom	*temp;

	temp = lst;
	if (temp->lstarg == NULL && temp->lstofredirin == NULL
		&& temp->lstofredirout == NULL)
		return (1);
	else
		return (0);
}

int	check_nbr_pipes(t_scom *lst)
{
	t_scom	*temp;

	temp = lst;
	if (check_node_empty(temp))
	{
		printf("syntax error near unexpected token `|\'\n");
		return (1);
	}
	temp = temp->next;
	while (temp != NULL)
	{
		if (check_node_empty(temp))
		{
			printf("pipe handling only between commands\n");
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}
