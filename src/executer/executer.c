/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:00:11 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/21 20:12:25 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

int	number_of_pipes(t_sCom *data)
{
	short	i;
	t_sCom	*tmp;

	tmp = data;
	i = 0;
	while (tmp->next)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

static void	do_builtin(t_msh *data, char *cmd)
{
	if (abs_string_cmp(cmd, "echo"))
		builtins_echo(data);
	else if (abs_string_cmp(cmd, "cd"))
		builtin_cd(data);
	else if (abs_string_cmp(cmd, "export"))
		builtin_export(data);
	else if (abs_string_cmp(cmd, "unset"))
		builtin_unset(data);
	else if (abs_string_cmp(cmd, "env"))
		builtin_env(data);
	else if (abs_string_cmp(cmd, "pwd"))
		builtin_pwd(data);
	else
		builtin_exit(data);
}

static bool	check_builtin(char *cmd)
{
	if (abs_string_cmp(cmd, "echo"))
		return (true);
	if (abs_string_cmp(cmd, "cd"))
		return (true);
	if (abs_string_cmp(cmd, "pwd"))
		return (true);
	if (abs_string_cmp(cmd, "export"))
		return (true);
	if (abs_string_cmp(cmd, "unset"))
		return (true);
	if (abs_string_cmp(cmd, "env"))
		return (true);
	if (abs_string_cmp(cmd, "exit"))
		return (true);
	return (false);
}

static void	execute_single_cmd(t_msh *data, char *path_cmd)
{
	char	**cmd;

	cmd = (char **)data->lst_cmd->argv;
	if (execve(path_cmd, cmd, data->env) < 0)
	{
		printf("error on execve\n");
		exit(1);
	}
		// msg erro + free all;
}

static char	*execute_condition(t_msh *data)
{
	char	*cmd;
	char	*path_cmd;

	cmd = (char *)data->lst_cmd->argv[0];
//	if (check_builtin(cmd))
//	{
//		do_builtin(data, cmd); APAGAR
//		return (NULL);
//	}
	path_cmd = check_access(data, cmd);
	if (!path_cmd)
	{
		ft_putstr_fd(cmd, 1);
		ft_putstr_fd(": command not found\n", 1);
		return (NULL);
	}
	return (path_cmd);
}

void	do_heredoc(t_msh *data)
{
//	(void)data;
	int 	tmp_fd;
	char	*buff;
	t_list	*tmp;
	t_redir	*tmp_red;


	tmp = data->lst_cmd->lstOfRedirIn;
	tmp_red = tmp->content;
	tmp_fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR);
	signal(SIGINT, SIG_DFL);
	if (tmp_fd < 0)
	{
		ft_putstr_fd("Error while opening file.\n", 2);
		free_all(data);
		exit(1);
	}
	while (1)
	{
		buff = readline(">");
		if (!buff)
		{
			ft_putstr_fd("minishell: warning: here-document at line 1 delimited by end-of-file\n", 2);
			break ;
		}
		buff[ft_strlen(buff)] = '\0';
		if (abs_string_cmp(tmp_red->filename, buff))
			break ;
		ft_putendl_fd(buff, tmp_fd);
		free(buff);
	}
	close(tmp_fd);
	free(buff);
	data->lst_cmd->ft_stdin = open(".heredoc",O_RDWR);
}

void	open_redir_in(t_msh *data)
{
	t_list	*tmp;
	t_redir	*tmp_red;

	tmp = data->lst_cmd->lstOfRedirIn;
	while(tmp)
	{
		tmp_red = tmp->content;
		if (tmp_red->type == LESS)
		{
			data->lst_cmd->ft_stdin = open(tmp_red->filename,O_RDONLY);
			if (data->lst_cmd->ft_stdin < 0)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(tmp_red->filename, 2);
				ft_putstr_fd(": no such file or directory\n", 2);
				free_all(data);
				exit(1);
			}
		}
		else if (tmp_red->type == LESSLESS)
		{
			do_heredoc(data);
		}
		tmp = tmp->next;
	}
}

void	open_redir_out(t_msh *data)
{
	t_list	*tmp;
	t_redir	*tmp_red;

	tmp = data->lst_cmd->lstOfRedirOut;
	while(tmp)
	{
		tmp_red = tmp->content;
		if (tmp_red->type == GREAT)
		{
			data->lst_cmd->ft_stdout = open(tmp_red->filename,O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
			if (data->lst_cmd->ft_stdout < 0)
			{
				ft_putstr_fd("Error while opening file.\n", 2);
				free_all(data);
				exit(1);
			}
		}
		else if (tmp_red->type == GREATGREAT)
		{
			data->lst_cmd->ft_stdout = open(tmp_red->filename,O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
			if (data->lst_cmd->ft_stdout < 0)
			{
				ft_putstr_fd("Error while opening file.\n", 2);
				free_all(data);
				exit(1);
			}
		}
		tmp = tmp->next;
	}
}

void	open_redir(t_msh *data)
{
	open_redir_in(data);
	open_redir_out(data);
}

void	do_redir(t_msh *data)
{
	open_redir(data);
}

void	close_pipes(t_msh *data)
{
	int i;

	i = 0;
	while (i < data->npipe)
	{
		close(data->fd[i][0]);
		close(data->fd[i][1]);
		i++;
	}
}

void	redirect_updt(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}

void	do_pipe(t_msh *data)
{
	t_sCom	*tmp;

	tmp = data->lst_cmd;
	if (tmp->i == 0)
		redirect_updt(tmp->ft_stdin,data->fd[0][1]);
	else if (tmp->i == data->npipe)
		redirect_updt(data->fd[data->npipe - 1][0],tmp->ft_stdout);
	else
		redirect_updt(data->fd[tmp->i - 1][0],data->fd[tmp->i][1]);
	close_pipes(data);
}

void	close_fd(t_msh *data)
{
	int	i;

	i = 3;
	while (i <= data->lst_cmd->ft_stdout || i <= data->lst_cmd->ft_stdin)
	{
		close(i);
		i++;
	}
	redirect_updt(STDIN_FILENO, STDOUT_FILENO);
}

static void	do_multiples_pipe(t_msh *data)
{
	char	*path_cmd;
	pid_t	pid;

	while(data->lst_cmd)
	{
		pid = fork();
		if (pid == 0)
		{
			do_redir(data);
			do_pipe(data);
			if (check_builtin(data->lst_cmd->argv[0]))
			{
				do_builtin(data, data->lst_cmd->argv[0]);
				close_pipes(data);
				exit(1);
			}
			path_cmd = execute_condition(data);
			if (!path_cmd)
				exit(0);
			execute_single_cmd(data, path_cmd);
		}
		data->lst_cmd = data->lst_cmd->next;
	}
}

static void	exit_or_update_env(t_msh *data, char *cmd)
{
	if (abs_string_cmp(cmd, "cd"))
		builtin_cd(data);
	else if (abs_string_cmp(cmd, "export"))
		builtin_export(data);
	else if (abs_string_cmp(cmd, "unset"))
		builtin_unset(data);
	else
		builtin_exit(data);
}

static void	do_no_pipe(t_msh *data)
{
	pid_t	pid;
	char	*cmd;
	char	*path_cmd;

	cmd = data->lst_cmd->argv[0];
	pid = fork();
	if (pid == 0)
	{
		do_redir(data);
		redirect_updt(data->lst_cmd->ft_stdin, data->lst_cmd->ft_stdout);
		if (check_builtin(cmd))
		{
			do_builtin(data, cmd);
			exit(1);
		}
		path_cmd = execute_condition(data);
		if (!path_cmd)
			exit(0);
		execute_single_cmd(data, path_cmd);
	}
	if (check_builtin(cmd))
		exit_or_update_env(data, cmd);
}

void	do_execute(t_msh *data)
{
	int		i;
	t_sCom	*tmp_lstcmd;

	init_signal(1);
	tmp_lstcmd = data->lst_cmd;
	i = -1;
	if (data->npipe > 0)
		do_multiples_pipe(data);
	else
		do_no_pipe(data);
	close_pipes(data);
	while (++i < data->nsCom)
		waitpid(0, NULL, 0);
	data->lst_cmd = tmp_lstcmd;
}


