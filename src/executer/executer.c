/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:00:11 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/15 23:27:24 by fvalli-v         ###   ########.fr       */
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

/*static void execute_multiple_cmd(void)
{
	;
}*/

static void	execute_single_cmd(t_msh *data, char *path_cmd)
{
	char	**cmd;

	cmd = (char **)data->lst_cmd->argv;
//	printf("ola %d\n", data->lst_cmd->i);
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
	if (check_builtin(cmd))
	{
		do_builtin(data, cmd);
		return (NULL);
	}
	path_cmd = check_access(data, cmd);
	if (!path_cmd)
	{
		ft_putstr_fd(cmd, 1);
		ft_putstr_fd(": command not found\n", 1);
		return (NULL);
	}
	return (path_cmd);
}

//void	do_heredoc(t_msh *data)
//{
//	(void)data;
//}
//
//void	open_redir_in(t_msh *data)
//{
//	t_list	*tmp;
//	t_redir	*tmp_red;
//
//	tmp = data->lst_cmd->lstOfRedirIn;
//	while(tmp)
//	{
//		tmp_red = tmp->content;
//		if (tmp_red->type == LESS)
//		{
//			data->lst_cmd->ft_stdin = open(tmp_red->filename,O_RDONLY);
//			if (data->lst_cmd->ft_stdin < 0)
//			{
//				ft_putstr_fd("minishell: ", 2);
//				ft_putstr_fd(tmp_red->filename, 2);
//				ft_putstr_fd(": no such file or directory\n", 2);
//				free_all(data);
//				exit(1);
//			}
//		}
//		else if (tmp_red->type == LESSLESS)
//		{
//			do_heredoc(data);
//		}
//		tmp = tmp->next;
//	}
//}
//
//void	open_redir_out(t_msh *data)
//{
//	t_list	*tmp;
//	t_redir	*tmp_red;
//
//	tmp = data->lst_cmd->lstOfRedirOut;
//	while(tmp)
//	{
//		tmp_red = tmp->content;
//		if (tmp_red->type == GREAT)
//		{
//			data->lst_cmd->ft_stdout = open(tmp_red->filename,O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
//			if (data->lst_cmd->ft_stdout < 0)
//			{
//				ft_putstr_fd("Error while opening file.\n", 2);
//				free_all(data);
//				exit(1);
//			}
//		}
//		else if (tmp_red->type == GREATGREAT)
//		{
//			data->lst_cmd->ft_stdout = open(tmp_red->filename,O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
//			if (data->lst_cmd->ft_stdout < 0)
//			{
//				ft_putstr_fd("Error while opening file.\n", 2);
//				free_all(data);
//				exit(1);
//			}
//		}
//		tmp = tmp->next;
//	}
//}
//
//void	open_redir(t_msh *data)
//{
//	open_redir_in(data);
//	open_redir_out(data);
//}
//
//void	do_redir(t_msh *data)
//{
//	open_redir(data);
//}
//
//void	close_pipes(t_msh *data)
//{
//	int i;
//
//	i = 0;
//	while (i < data->npipe)
//	{
//		close(data->fd[i][0]);
//		close(data->fd[i][1]);
//		i++;
//	}
//}
//
//void	do_pipe(t_msh *data)
//{
//	//fazer os dup e dup2 para conectar os processos pelos pipes.
//	//lembrar que o primeiro comando e o ultimo s'ao diferentes.
//	//no primeiro le do stdin e escreve no pipe (write end fd[i][1])
//	//o ultimo le do pipe e escreve no stdout
//	t_sCom	*tmp;
//
//	tmp = data->lst_cmd;
//	if (tmp->i == 0)
//	{
//		dup2(tmp->ft_stdin, STDIN_FILENO);
//		dup2(data->fd[0][1], STDOUT_FILENO);
//	}
//	else if (tmp->i == data->npipe)
//	{
//		dup2(data->fd[data->npipe - 1][0], STDIN_FILENO);
//		dup2(tmp->ft_stdout, STDOUT_FILENO);
//	}
//	else
//	{
//		dup2(data->fd[tmp->i - 1][0], STDIN_FILENO);
//		dup2(data->fd[tmp->i][1], STDOUT_FILENO);
//	}
//	close_pipes(data);
//}
//
//void	do_execute(t_msh *data)
//{
//	char	*path_cmd;
//	pid_t	pid;
////	int		i;
////
////	i = 0;
//	if (data->npipe > 0)
//	{
//		while(data->lst_cmd)
//		{
//			pid = fork();
//			if (pid == 0)
//			{
////				printf("Start child process\n");
//				do_redir(data);
//				do_pipe(data);
//				path_cmd = execute_condition(data); //alterar data para data->lst_cmd
//				if (!path_cmd)
//				{
//					free_all(data);
//					exit(0);
//				}
//				execute_single_cmd(data, path_cmd); // alterar data para data->lst_cmd
//			}
//			data->lst_cmd = data->lst_cmd->next;
//		}
//	}
//	else
//	{
//		//execute_condition garante que o fork só sera feito para caso o comando não seja builtin
//		//no single comand nao precisa de pipe somente de redirecionar
//		dup2(data->lst_cmd->ft_stdin, STDIN_FILENO);
//		dup2(data->lst_cmd->ft_stdout, STDOUT_FILENO);
//		path_cmd = execute_condition(data);
//		if (!path_cmd)
//			return ;
//		pid = fork();
//		if (pid == 0)
//			execute_single_cmd(data, path_cmd);
//	}
////	while (i < data->nsCom)
////	{
////		waitpid(-1, NULL, 0);
////		i++;
////	}
//	free (path_cmd);
//	close_pipes(data);
//}

void	do_execute(t_msh *data)
{
	char	*path_cmd;
	pid_t	pid;

	path_cmd = execute_condition(data);
	if (!path_cmd)
		return ;
	pid = fork();
	if (pid == 0)
		execute_single_cmd(data, path_cmd);
	waitpid(pid, NULL, 0);
	free (path_cmd);
}
