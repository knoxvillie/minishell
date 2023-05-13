/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:29:44 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/13 12:35:58 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// * Includes *
# include "./libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>


// * Includes Header *


// * Macros *
typedef struct s_env	t_env;

typedef struct s_sCom {
    char			**argv;
    t_list			*lstArg;
    t_list			*lstOfRedirIn;
    t_list			*lstOfRedirOut;
//    int ft_stdin = STDIN_FILENO;
//    int ft_stdout = STDOUT_FILENO;
    struct s_sCom	*next; //t_sCom *next; I'll use to check the numbers of pipes
} t_sCom;

typedef struct s_redir {
    int     type;
    char    *filename;
} t_redir;

struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
};

typedef struct s_ppt
{
	int		n_exec;
	char	*prompt;
	char	*user;
	char	*s_manager;
	char	*home;
	char	*path;
	char	*abs_path;
	t_env	*list;
}		t_ppt;

// This is the super class
typedef struct s_msh
{
	t_ppt	*ppt;
	t_sCom	*lst_cmd;
	char	**env;
}		t_msh;

// *** BUILTINS ***
void	builtin_unset(t_msh *data);
void	builtin_export(t_msh *data);
void	builtin_env(t_msh *data);
void	builtin_pwd(t_msh *data);
// *** Functions ***
//void	ft_parser(char *input);
// * env_list.c
t_msh	*env_to_list(t_msh *data, char **env);
t_env	*init_env_node(char *key, char *value);
t_env	*stack_env_list(t_env *var, t_env *node);
// * list_handle.c
char	*get_value_from_key(t_env *header, char *key);
char	*get_key_address(t_env *env, char *key);
void	modify_value(t_msh *data, char *key, char *new_value);
bool	is_key_in_env(t_env *env, char *key);
bool	abs_string_cmp(char *s1, char *s2);
// * utils.c
void	put_string_exit(char *str, int flag);
void	free_t_env(t_env *list);
void	free_t_ppt(t_ppt *root);
bool	check_syntax_prompt(char *input);
void	init_env_table(t_msh *data);
void	free_table(char **table);
// * prompt.c
char	*display_prompt(t_ppt *root);
char	*check_access(t_msh *data, char *cmd);
void	do_execute(t_msh *data);
#endif
