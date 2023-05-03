/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:14:58 by kfaustin          #+#    #+#             */
/*   Updated: 2023/04/21 14:29:41 by kfaustin         ###   ########.fr       */
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
# define METACH "|&;()<>"


//Command table is an array of struct SimpleCommands(sCom)  -  Simple Commands as said by GNU manual:
//A simple command is the kind of command encountered most often. It’s just a sequence of words separated by blanks,
// terminated by one of the shell’s control operators (see Definitions). The first word generally specifies a command to be executed,
// with the rest of the words being that command’s arguments.

//echo  > kelvin  > kelvin > kelvin > kelvin > kelvin > kelvin > kelvin > kelvin kelvin fabio valli vieira > fabio > test
//echo  > kelvin  kelvin fabio valli vieira > fabio > test
typedef struct s_sCom {
    int     id;
    t_list  **lstOfWords;
    char    **argList;
    int     numOfArg;
    t_list  **lstOfRedirIn;
    t_list  **lstOfRedirOut;
} t_sCom;

typedef struct s_redir {
    int     type;
    char    *filename;
} t_redir;

typedef struct s_word {
    char *word;
} t_word;

typedef struct s_tokens
{
	char	*cmd;
	char	*flag;
	char	*complement;
	char	**tokens;
}		t_tokens;

#endif
