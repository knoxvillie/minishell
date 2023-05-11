/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:14:58 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/10 10:20:46 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# define GREAT 1
# define GREATGREAT 2
# define LESS 3
# define LESSLESS 4
# define DQUOTE 5
# define SQUOTE 6
# define WSPACE " \t\r\n\v"
# define METACH "|<>"
# define UNSUPMETACH "&;()*{}\\"


//Command table is an array of struct SimpleCommands(sCom)  -  Simple Commands as said by GNU manual:
//A simple command is the kind of command encountered most often. It’s just a sequence of words separated by blanks,
// terminated by one of the shell’s control operators (see Definitions). The first word generally specifies a command to be executed,
// with the rest of the words being that command’s arguments.

//echo  > kelvin  > kelvin > kelvin > kelvin > kelvin > kelvin > kelvin > kelvin kelvin fabio valli vieira > fabio > test
//echo  > kelvin  kelvin fabio valli vieira > fabio > test



t_sCom	*ft_lstlastsCom(t_sCom *lst);
t_sCom	*ft_lstnewsCom(void);
void	ft_lstadd_backsCom(t_sCom **lst, t_sCom *new);

int		redirout(t_msh	*data, char **str);
int		redirin(t_msh	*data, char **str);
int		get_token_pipe(t_msh	*data, char **str);
void	get_token_dsq(t_msh	*data, char **str);
void	get_token_word(t_msh	*data, char **str);
int		ft_parse(char	*input, t_msh	*data);
void	free_lst(t_list **lst);
void	free_lstsCom(t_sCom **lst);
int check_node_empty(t_sCom *lst);
int check_nbr_pipes(t_sCom *lst);

#endif
