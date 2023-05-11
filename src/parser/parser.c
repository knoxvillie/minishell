/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:25:58 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/03 10:41:40 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
# include "../../includes/parser.h"

//Print function for Ctable (Command Table)
void print_lstCtable(t_msh *data)
{
    t_sCom *lst;
//    t_sCom *head;
    int i;

    i = 0;
    lst = data->lst_cmd;
//    lst = data->lst_cmd;
//    head = data->lst_cmd;
    t_list *tmp;
    while (lst)
    {
        printf("Simple command number %d\n", i);
        printf("List of args\n");
        tmp = lst->lstArg;
        while(tmp)
        {
            printf("%s\n",(char *)(tmp->content));
            tmp = tmp->next;
        }
        printf("List of redir out\n");
        tmp = lst->lstOfRedirOut;
        while(tmp)
        {
            t_redir *temp = (t_redir *)(tmp->content);
            printf("%d\n",temp->type);
            printf("%s\n",temp->filename);
            tmp = tmp->next;
        }
        printf("List of redir in\n");
        tmp = lst->lstOfRedirIn;
        while(tmp)
        {
            t_redir *temp1 = (t_redir *)(tmp->content);
            printf("%d\n",temp1->type);
            printf("%s\n",temp1->filename);
            tmp = tmp->next;
        }
        i++;
        lst = lst->next;
    }
}

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

int    get_token(t_msh	*data, char **str)
{
    while (**str && ft_strchr(WSPACE, **str))
        (*str)++;
    if (**str== '|')
        return (get_token_pipe(data, str));
    else if (**str == '<')
        return (redirin(data, str));
    else if (**str == '>')
        return (redirout(data, str));
    else if (**str && ft_strchr(UNSUPMETACH, **str))
        return (printf("Minishell does not support this operator %c\n",**str), (*str)++, 1);
    else
        get_token_word(data, str);
    return (0);
}

void	init_arglist(t_msh *data, int num)
{
	short	i;
	t_list	*node;

	data->lst_cmd->argList = NULL;
	i = 0;
	node = data->lst_cmd->lstArg;
	data->lst_cmd->argList = (char **)malloc(sizeof(char *) * (num + 1));
	if (!data->lst_cmd->argList)
		ft_putstr_fd("Error: Malloc of argList is null", 2);
	while (i < num)
	{
		data->lst_cmd->argList[i] = node->content;
		i++;
		node = node->next;
	}
	data->lst_cmd->argList[i] = NULL;
}

int ft_parse(char *input, t_msh *data){

    char	*str;
	int		num;

	num = 0;
    str = input;
    if (!check_unclosed_quotes(input))
    {
        ft_putstr_fd("Error: Unclosed quotes found\n", 2);
        return (1);
    }
    ft_lstadd_backsCom(&(data->lst_cmd), ft_lstnewsCom());
    while (*str)
    {
        if (get_token(data, &str))
            return (1);
		num++;
    }
    print_lstCtable(data);
    if (check_nbr_pipes(data->lst_cmd))
        return (1);
	init_arglist(data, num);
    return (0);
}

//Main to test the parsing
//int main(int argc, char **argv)
//{
//    t_msh   *data;
//
//    data = (t_msh *)malloc(sizeof(t_msh));
//    data = (t_msh *)ft_memset(data, 0, sizeof(t_msh));
//    data->lst_cmd = NULL;
//    if (argc == 2)
//    {
//        if (ft_parse(argv[1], data))
//            printf("error\n");
//        printf("OK\n");
//        print_lstCtable(data);
//    }
//    else
//        printf("incorrect number of args\n");
//    return (0);
//}












/*void	ft_parser(t_tokens *parser, char *str)
{
	int	i;

	i = 0;
	parser->tokens = ft_split(str, ' ');
	parser->cmd = parser->tokens[i++];
	parser->flag = parser->tokens[i++];
	parser->complement = parser->tokens[i];
}*/

//void	ft_parser(char *input)
//{
//	int		i;
//	int		n_pipes;
//	char	**cmds;
//
//	i = -1;
//	n_pipes = 0;
//	while (input[++i])
//		if (input[i] == '|')
//			n_pipes++;
//	if (n_pipes >= 1)
//		cmds = ft_split(input, '|');
//}
/*void	ft_parser(t_tokens *parser, char *str)
{
	int	i;

	i = 0;
	parser->tokens = ft_split(str, ' ');
	parser->cmd = parser->tokens[i++];
	parser->flag = parser->tokens[i++];
	parser->complement = parser->tokens[i];
}*/
//
//void	ft_parser(char *input)
//{
//	int		i;
//	int		j;
//	int		n_pipes;
//	char	**cmds;
//
//	cmds = NULL;
//	i = -1;
//	n_pipes = 0;
//	while (input[++i])
//		if (input[i] == '|')
//			n_pipes++;
//	printf("%d", n_pipes);
//	if (n_pipes >= 1) {
//		cmds = ft_split(input, '|');
//	}
//	i = -1;
//	while (cmds[++i])
//	{
//		j = 0;
//		while (cmds[i][j])
//		{
//			printf("%c", cmds[i][j]);
//			j++;
//		}
//		printf("\n");
//	}
//}