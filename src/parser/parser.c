/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:25:58 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/21 00:08:53 by fvalli-v         ###   ########.fr       */
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

int size_lstArg(t_sCom *data)
{
    t_list *tmp;
    int		i;

    tmp = data->lstArg;
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

void	init_argv(t_msh *data)
{
	int		i;
	int		nsCom;
	t_list	*tmpArgLst;
	t_sCom	*tmpsCom;

	tmpsCom = data->lst_cmd;
	nsCom = 0;
	while (tmpsCom != NULL)
	{
		i = size_lstArg(tmpsCom);
		tmpArgLst = tmpsCom->lstArg;
		tmpsCom->i = nsCom;
		tmpsCom->argv = (char **)malloc(sizeof(char *) * (i + 1));
		if (!tmpsCom->argv)
		{
			ft_putstr_fd("Error: Malloc of argList is null", 2);
			// free and exit
		}
        i = 0;
        while (tmpArgLst != NULL)
        {
			//caso primeiro elemento de tmpArgLst->content seja nulo n'ao faz ft_strdup
			if (tmpArgLst->content)
			{
				tmpsCom->argv[i] = ft_strdup((char *)tmpArgLst->content);
				i++;
			}
			tmpArgLst = tmpArgLst->next;
		}
		tmpsCom->argv[i] = NULL;
		nsCom++;
		tmpsCom = tmpsCom->next;
	}
	data->nsCom = nsCom;
	data->npipe = nsCom - 1;
}

int ft_parse(char *input, t_msh *data)
{
	char	*str;
	t_sCom	*tmp;

	str = input;
	if (!check_unclosed_quotes(input))
	{
		ft_putstr_fd("Error: Unclosed quotes found\n", 2);
		return (1);
	}
	tmp = ft_lstnewsCom();
	ft_lstadd_backsCom(&(data->lst_cmd), tmp);
	while (*str)
	{
		if (get_token(data, &str))
			return (1);
	}
	if (check_nbr_pipes(data->lst_cmd))
		return (1);
	//
	expander(data);
	init_argv(data);
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