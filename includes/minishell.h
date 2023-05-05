/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:29:44 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/05 16:08:13 by kfaustin         ###   ########.fr       */
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

typedef struct s_ppt
{
	int		n_exec;
	char	*prompt;
	char	*user;
	char	*s_manager;
	char	*home;
	char	*path;
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
void	builtin_unset(t_env *env, char *str);
void	builtin_export(t_ppt *root, char *str);

// *** Functions ***
void	ft_parser(char *input);
// * env_list.c
void	env_to_list(t_ppt *root, char **env);
void	init_env_node(t_env **node, char *key, char *value);
void	stack_env_list(t_ppt *root, t_env *node);
// * list_handle.c
char	*get_value_from_key(t_env *header, char *key);
bool	is_key_in_env(t_env *env, char *key);
bool	abs_string_cmp(char *s1, char *s2);
// * utils.c
void	put_string_exit(char *str, int flag);
void	free_t_env(t_env *list);
void	free_t_ppt(t_ppt *root);
bool	check_syntax_prompt(char *input);
// * prompt.c
char	*display_prompt(t_ppt *root);
char	*check_access(t_env *env, char *cmd);
void	do_execute(t_msh *data);
#endif
