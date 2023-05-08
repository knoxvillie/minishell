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
    int i;

    i = 0;
    lst = data->lst_cmd;
    while (lst)
    {
        printf("Simple command number %d\n", i);
        printf("List of args\n");
        while(lst->lstArg)
        {
            printf("%s\n",(char *)(lst->lstArg->content));
            lst->lstArg = lst->lstArg->next;
        }
        printf("List of redir out\n");
        while(lst->lstOfRedirOut)
        {
            t_redir *tmp = (t_redir *)(lst->lstOfRedirOut->content);
            printf("%d\n",tmp->type);
            printf("%s\n",tmp->filename);
            lst->lstOfRedirOut = lst->lstOfRedirOut->next;
        }
        printf("List of redir in\n");
        while(lst->lstOfRedirIn)
        {
            t_redir *tmp1 = (t_redir *)(lst->lstOfRedirIn->content);
            printf("%d\n",tmp1->type);
            printf("%s\n",tmp1->filename);
            lst->lstOfRedirIn = lst->lstOfRedirIn->next;
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

int ft_parse(char	*input, t_msh	*data){

    char *str;

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
    }
    print_lstCtable(data);
    //verificar se há um node a mais que o numero de pipes e se estes estao preenchidos.
    //caso nao seja valido
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