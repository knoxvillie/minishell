/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:14:58 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/27 15:54:44 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "./minishell.h"

# define GREAT 1
# define GREATGREAT 2
# define LESS 3
# define LESSLESS 4
# define WSPACE " \t\r\n\v"
# define METACH "|<>"
# define UNSUPMETACH "&;()*{}\\"

void	init_argv(t_msh *data);
t_scom	*ft_lstlastscom(t_scom *lst);
t_scom	*ft_lstnewscom(void);
void	ft_lstadd_backscom(t_scom **lst, t_scom *new);

int		redirout(t_msh	*data, char **str);
int		redirin(t_msh	*data, char **str);
int		get_token_pipe(t_msh	*data, char **str);
void	get_token_word(t_msh	*data, char **str);
int		ft_parse(char	*input, t_msh	*data);
void	free_lst(t_scom *lst);
void	free_lstscom(t_msh *lst);
int		check_node_empty(t_scom *lst);
int		check_nbr_pipes(t_scom *lst);

#endif
