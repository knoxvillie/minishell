/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:39:42 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/20 23:24:37 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by fvalli-v on 07-05-2023.
//

# include "../../includes/minishell.h"
# include "../../includes/parser.h"

t_scom	*ft_lstlastsCom(t_scom *lst)
{
    t_scom	*temp;

    if (!lst)
        return (NULL);
    temp = lst;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    return (temp);
}
//
t_scom	*ft_lstnewsCom(void)
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

void	ft_lstadd_backsCom(t_scom **lst, t_scom *new)
{
    t_scom	*temp;

    if (!lst || !new) //lst nunca vai ser nulo aqui.
        return ;
    if (*lst == NULL)
        *lst = new;
    else
    {
        temp = ft_lstlastsCom(*lst);
        temp->next = new;
    }
}
void	free_lst(t_list *lst)
{
	t_list	*next;

	if (lst == NULL)
		return ;
	while (lst)
	{
		next = lst->next;
		if (lst->content)
			free(lst->content);
		free(lst);
		lst = next;
	}
}

void	free_lstsCom(t_msh *data)
{
	t_scom	*next;

	if (data->lst_cmd == NULL)
		return ;
	while (data->lst_cmd)
	{
		next = data->lst_cmd->next;
		free_table(data->lst_cmd->argv);
		free_lst(data->lst_cmd->lstarg);
		free_lst(data->lst_cmd->lstofredirin);
		free_lst(data->lst_cmd->lstofredirout);
		free(data->lst_cmd);
		data->lst_cmd = next;
	}
}

int check_node_empty(t_scom *lst)
{
    t_scom *temp;

    temp = lst;
    if (temp->lstarg == NULL && temp->lstofredirin == NULL && temp->lstofredirout == NULL)
        return (1);
    else
        return (0);
}

int check_nbr_pipes(t_scom *lst)
{
    t_scom *temp;
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

int jump_dq_and_sq(char **str, int i)
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

int get_token_word_redir(t_msh	*data, char **str, int type)
{
    int     i;
    t_scom *sCom;
    t_redir *red;

    red = (t_redir *)malloc(sizeof(t_redir));
    red->type = type;
    sCom = ft_lstlastsCom(data->lst_cmd);
    while (**str && ft_strchr(WSPACE, **str))
        (*str)++;
    if (**str && (ft_strchr(METACH, **str) || ft_strchr(UNSUPMETACH, **str)))
        return (printf("syntax error near unexpected token `%c\'\n",**str), 1);
    if (**str == '\0')
        return (printf("syntax error near unexpected token `newline\'\n"), 1);
    red->filename = ft_strdup(*str);
    i = 0;
    while (**str && !ft_strchr(WSPACE, **str) && !ft_strchr(METACH, **str) && !ft_strchr(UNSUPMETACH, **str))
    {
        i = jump_dq_and_sq(str, i);
        (*str)++;
        i++;
    }
    red->filename[i] = '\0';
    if (type == GREATGREAT || type == GREAT)
        return (ft_lstadd_back(&(sCom->lstofredirout), ft_lstnew(red)), 0);
    else
        return (ft_lstadd_back(&(sCom->lstofredirin), ft_lstnew(red)), 0);
}

int redirout(t_msh	*data, char **str)
{
    (*str)++;
    if (**str == '>')
        return ((*str)++, get_token_word_redir(data, str, GREATGREAT));
    else
        return (get_token_word_redir(data, str, GREAT));
}

int redirin(t_msh	*data, char **str)
{
    (*str)++;
    if (**str == '<')
        return ((*str)++, get_token_word_redir(data, str, LESSLESS));
    else
        return (get_token_word_redir(data, str, LESS));
}
int get_token_pipe(t_msh *data, char **str)
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
    return (ft_lstadd_backsCom(&(data->lst_cmd), ft_lstnewsCom()), 0);
}

void get_token_word(t_msh *data, char **str)
{
    char    *tmp;
    int     i;
    t_scom *sCom;

    sCom = ft_lstlastsCom(data->lst_cmd);
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
		ft_lstadd_back(&(sCom->lstarg), ft_lstnew(tmp));
}