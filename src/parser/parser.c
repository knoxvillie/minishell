/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:25:58 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/08 14:27:52 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
# include "../../includes/parser.h"

/*==288062== Conditional jump or move depends on uninitialised value(s)
==288062==    at 0x4027F1: ft_lstlastsCom (parser_utils.c:15)
==288062==    by 0x4028E4: ft_lstadd_backsCom (parser_utils.c:46)
==288062==    by 0x402775: ft_parse (parser.c:68)
==288062==    by 0x40162E: main_loop (main.c:45)
==288062==    by 0x4016B1: main (main.c:74)
==288062==  Uninitialised value was created by a heap allocation
==288062==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==288062==    by 0x401729: init_data (main.c:61)
==288062==    by 0x4016A4: main (main.c:73)
==288062==*/

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

int ft_parse(t_msh *data, char *input){

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
	//verificar se há um node a mais que o numero de pipes e se estes estao preenchidos.
	//caso nao seja valido
	return (0);
}

/*int ft_parse(t_msh *data, char *input){

    char *str;
	t_sCom	*new_node;

    str = input;
    if (!check_unclosed_quotes(input))
    {
        ft_putstr_fd("Error: Unclosed quotes found\n", 2);
        return (1);
    }
	(void)str;
	data->lst_cmd = NULL; //
	new_node = ft_lstnewsCom();
	//ft_lstadd_backsCom(&(data->lst_cmd), ft_lstnewsCom());
	ft_lstadd_backsCom(&(data->lst_cmd), new_node);
	data->lst_cmd->lstArg->content = input;

	*//*while (*str)
    {
        if (get_token(data, &str))
            return (1);
    }*//*
    //verificar se há um node a mais que o numero de pipes e se estes estao preenchidos.
    //caso nao seja valido
    return (0);
}*/

//Print function for Ctable (Command Table)
//void print_lstCtable(t_msh *data)
//{
//    t_sCom *lst;
//    int i;
//
//    i = 0;
//    lst = data->lst_cmd;
//    while (lst)
//    {
//        printf("Simple command number %d\n", i);
//        printf("List of args\n");
//        while(lst->lstArg)
//        {
//            printf("%s\n",(char *)(lst->lstArg->content));
//            lst->lstArg = lst->lstArg->next;
//        }
//        printf("List of redir out\n");
//        while(lst->lstOfRedirOut)
//        {
//            t_redir *tmp = (t_redir *)(lst->lstOfRedirOut->content);
//            printf("%d\n",tmp->type);
//            printf("%s\n",tmp->filename);
//            lst->lstOfRedirOut = lst->lstOfRedirOut->next;
//        }
//        printf("List of redir in\n");
//        while(lst->lstOfRedirIn)
//        {
//            t_redir *tmp1 = (t_redir *)(lst->lstOfRedirIn->content);
//            printf("%d\n",tmp1->type);
//            printf("%s\n",tmp1->filename);
//            lst->lstOfRedirIn = lst->lstOfRedirIn->next;
//        }
//        i++;
//        lst = lst->next;
//    }
//}

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