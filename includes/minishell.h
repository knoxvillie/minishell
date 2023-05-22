/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:29:44 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/21 21:14:20 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>


extern int	exit_status;

typedef struct s_env	t_env;
typedef struct s_sCom	t_sCom;

typedef struct s_sCom {
	int		i;
	char	**argv;
	t_list	*lstArg;
	t_list	*lstOfRedirIn;
	t_list	*lstOfRedirOut;
	int		ft_stdin;
	int		ft_stdout;
	t_sCom	*next;
} t_sCom;

typedef struct s_redir {
	int		type;
	char	*filename;
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

typedef struct s_exp
{
	t_env	*env;
	t_env	*exp;
}		t_exp;

typedef struct s_msh
{
	int		npipe;
	int		nsCom;
	int		**fd;
	t_ppt	*ppt;
	t_sCom	*lst_cmd;
	char	**env;
	t_exp	*export;
}		t_msh;

//  ------------- *** Functions *** ------------- |
//
// *** BUILTINS *** ------------------------------|
void	builtins_echo(t_msh *data);
void	builtin_unset(t_msh *data);
void	builtin_export(t_msh *data);
void	builtin_env(t_msh *data);
void	builtin_pwd(t_msh *data);
// * *----------* *| (cd.c):
void	builtin_cd(t_msh *data);
void	builtin_cd_update(t_msh *data);
char	*do_dot(t_msh *data);
//-----------------|
void	builtin_exit(t_msh *data);

// *** EXECUTER *** ------------------------------|
// * *----------* *| (access.c):
char	*check_access(t_msh *data, char *cmd);
// * *----------* *| (executer.c):
void	do_execute(t_msh *data);
void	close_pipes(t_msh *data);
// *** PARSER *** --------------------------------|
//
// *** SRC *** -----------------------------------|
// * *----------* *| (create_pipe.c):
void	create_pipe(t_msh *data);
// * *----------* *| (free.c):
void	free_all(t_msh *data);
void	free_over(t_msh *data);
void	free_prompt(t_ppt *root);
void	free_table(char **table);
void	free_t_exp(t_env *list);
void	free_t_env(t_env *list);
void	free_fd(t_msh *data);
// * *----------* *| (generic.c):
void	put_str_exit(char *str, int flag);
bool	abs_string_cmp(char *s1, char *s2);
int		size_of_list(t_env *lst);
bool	ptr_is_digit(char *str);
// * *----------* *| (init.c):
t_msh	*init_data(t_msh *data, char **env);
void	init_env_table(t_msh *data);
// * *----------* *| (prompt.c):
char	*display_prompt(t_ppt *root);
// * *----------* *| (signals.c):
void	init_signal(int flag);
void	init_signal_heredoc(void);
// * *----------* *| (t_env_list.c):
t_env	*init_env_node(char *key, char *value);
t_env	*stack_env_list(t_env *var, t_env *node);
t_msh	*env_to_list(t_msh *data, char **env);
// * *----------* *| (t_env_list2.c):
char	*get_value_from_key(t_env *env, char *key);
void	modify_value(t_msh *data, char *key, char **new_value);
bool	is_key_in_env(t_env *env, char *key);
// * *----------* *| (expander.c):
void	expander(t_msh *data);



#endif
