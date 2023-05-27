/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:29:44 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/27 15:55:19 by kfaustin         ###   ########.fr       */
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

extern int	g_exit_status;

typedef struct s_scom {
	int				i;
	char			**argv;
	t_list			*lstarg;
	t_list			*lstofredirin;
	t_list			*lstofredirout;
	int				ft_stdin;
	int				ft_stdout;
	struct s_scom	*next;
}		t_scom;

typedef struct s_redir {
	int			type;
	char		*filename;
}		t_redir;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}		t_env;

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

typedef struct s_exp
{
	t_env	*env;
	t_env	*exp;
}		t_exp;

typedef struct s_expan
{
	int		size;
}		t_expan;

typedef struct s_msh
{
	int		npipe;
	int		nscom;
	int		**fd;
	int		heredoc;
	char	**env;
	int		num;
	pid_t	*pid;
	t_ppt	*ppt;
	t_scom	*lst_cmd;
	t_exp	*export;
}		t_msh;

//  ------------- *** Functions *** ------------- |
//
// *** BUILTINS *** ------------------------------|
void	builtins_echo(t_msh *data);
// * *----------* *| (unset.c):
void	builtin_unset(t_msh *data);
bool	check_env_till_end(t_msh *data, char *str);
bool	check_env_first_node(t_msh *data, char *str);
bool	check_exp_till_end(t_msh *data, char *str);
bool	check_exp_first_node(t_msh *data, char *str);
// * *----------* *| (unset_update.c):
void	builtin_unset_update(t_msh *data);
bool	check_ue_syntax_up(char *str);
bool	check_ue_syntax(char *str, char *mode);
// * *----------* *| (export.c):
void	builtin_export(t_msh *data);
void	builtin_export_update(t_msh *data);
// * *----------* *| (env.c):
void	builtin_env(t_msh *data);
void	builtin_pwd(t_msh *data);
// * *----------* *| (cd.c):
void	builtin_cd(t_msh *data);
void	builtin_cd_update(t_msh *data);
// * *----------* *| (exit.c):
void	builtin_exit(t_msh *data);
void	builtin_exit_update(t_msh *data);

// *** EXECUTER *** ------------------------------|
// * *----------* *| (access.c):
char	*check_access(char *path, char *cmd);
// * *----------* *| (executer.c):
void	do_execute(t_msh *data);
void	close_pipes(t_msh *data);
// *** PARSER *** --------------------------------|
//
// *** EXPANDER *** ------------------------------|
void	expander(t_msh *data);
void	check_expander(t_msh *data, void **content);
int		is_alnumunder(int c);
// *** SRC *** -----------------------------------|
// * *----------* *| (create_pipe.c):
void	create_pipe(t_msh *data);
void	do_pipe(t_msh *data);
// * *----------* *| (dobuiltin.c):
void	exit_or_update_env(t_msh *data, char *cmd);
void	do_builtin(t_msh *data, char *cmd);
bool	check_builtin(char *cmd);
// * *----------* *| (free.c):
void	free_all(t_msh *data);
void	free_over(t_msh *data);
void	free_prompt(t_ppt *root);
void	free_table(char **table);
void	free_fork(t_msh *data);
// * *----------* *| (free2.c):
void	free_t_env(t_env *list);
void	free_fd(t_msh *data);
void	free_t_exp(t_env *list);
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
// * *----------* *| (redirect.c):
void	do_heredoc(t_msh *data);
void	open_redir_in(t_msh *data);
void	open_redir_out(t_msh *data);
// * *----------* *| (redirect2.c):
void	open_redir(t_msh *data);
void	do_redir(t_msh *data);
void	redirect_updt(int in, int out);
// * *----------* *| (signals.c):
void	init_signal(int flag);
void	init_signal_heredoc(void);
// * *----------* *| (t_env_list.c):
t_env	*init_env_node(char *key, char *value);
t_env	*stack_env_list(t_env *var, t_env *node);
t_msh	*env_to_list(t_msh *data, char **env);
// * *----------* *| (t_env_list2.c):
char	*get_value_from_key(t_env *env, char *key);
void	modify_value_exp(t_msh *data, char *key, char **new_value);
void	modify_value(t_msh *data, char *key, char **new_value);
bool	is_key_in_env(t_env *env, char *key);
// * *----------* *| (handle_exit.c):
void	get_exit_status(t_msh *data);

#endif
