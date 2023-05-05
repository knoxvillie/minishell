/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:29:44 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/05 11:46:20 by kfaustin         ###   ########.fr       */
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

// * Includes Header *
# include "parser.h"

// * Macros *
typedef struct s_env	t_env;

struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
};

typedef struct s_root
{
	int		n_exec;
	char	*prompt;
	char	*user;
	char	*s_manager;
	char	*home;
	char	*p_path;
	t_env	*list;
}		t_root;

// This is the super class
typedef struct s_msh
{
	t_root	*ppt;
	t_sCom	*lst_cmd;
}		t_msh;

// *** BUILTINS ***
void	builtin_unset(t_env *env, char *str);
void	builtin_export(t_root *root, char *str);

// *** Functions ***
void	ft_parser(char *input);
// * env_list.c
void	env_to_list(t_root *root, char **env);
void	init_env_node(t_env **node, char *key, char *value);
void	stack_env_list(t_root *root, t_env *node);
// * list_handle.c
char	*get_value_from_key(t_env *header, char *key);
bool	is_key_in_env(t_env *env, char *key);
bool	abs_string_cmp(char *s1, char *s2);
// * utils.c
void	put_string_exit(char *str, int flag);
void	free_t_env(t_env *list);
void	free_t_root(t_root *root);
bool	check_syntax_prompt(char *input);
// * prompt.c
char	*display_prompt(t_root *root);
#endif
