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

/*void	ft_parser(t_tokens *parser, char *str)
{
	int	i;

	i = 0;
	parser->tokens = ft_split(str, ' ');
	parser->cmd = parser->tokens[i++];
	parser->flag = parser->tokens[i++];
	parser->complement = parser->tokens[i];
}*/

void	ft_parser(char *input)
{
	int		i;
	int		n_pipes;
	char	**cmds;

	i = -1;
	n_pipes = 0;
	while (input[++i])
		if (input[i] == '|')
			n_pipes++;
	if (n_pipes >= 1)
		cmds = ft_split(input, '|');
}
/*void	ft_parser(t_tokens *parser, char *str)
{
	int	i;

	i = 0;
	parser->tokens = ft_split(str, ' ');
	parser->cmd = parser->tokens[i++];
	parser->flag = parser->tokens[i++];
	parser->complement = parser->tokens[i];
}*/

void	ft_parser(char *input)
{
	int		i;
	int		j;
	int		n_pipes;
	char	**cmds;

	cmds = NULL;
	i = -1;
	n_pipes = 0;
	while (input[++i])
		if (input[i] == '|')
			n_pipes++;
	printf("%d", n_pipes);
	if (n_pipes >= 1) {
		cmds = ft_split(input, '|');
	}
	i = -1;
	while (cmds[++i])
	{
		j = 0;
		while (cmds[i][j])
		{
			printf("%c", cmds[i][j]);
			j++;
		}
		printf("\n");
	}
}