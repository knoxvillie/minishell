/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:00:11 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/27 14:47:05 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execute_execve(t_msh *data, char *path_cmd)
{
	char	**cmd;

	cmd = (char **)data->lst_cmd->argv;
	if (execve(path_cmd, cmd, data->env) < 0)
	{
		printf("msh: error on execve\n");
		exit(1);
	}
}

static char	*execute_condition(t_msh *data)
{
	char	*cmd;
	char	*path;
	char	*path_cmd;

	if (*data->lst_cmd->argv == NULL)
		return (NULL);
	cmd = strdup((char *)data->lst_cmd->argv[0]);
	path = get_value_from_key(data->ppt->list, "PATH");
	if (!path)
	{
		free (cmd);
		free (path);
		return (ft_putstr_fd("msh: No such file or dir\n", 2), NULL);
	}
	if (access(cmd, X_OK) == 0)
		return (free(path), cmd);
	path_cmd = check_access(path, cmd);
	free (path);
	free (cmd);
	if (!path_cmd)
	{
		ft_putstr_fd("msh: command not found\n", 2);
		g_exit_status = 127;
		return (NULL);
	}
	return (path_cmd);
}

static void	do_multiples_pipe(t_msh *data)
{
	char	*path_cmd;

	while(data->lst_cmd)
	{
		if (data->heredoc)
			wait(0);
		data->pid[data->lst_cmd->i] = fork();
		if (data->pid[data->lst_cmd->i] == 0)
		{
			do_redir(data);
			do_pipe(data);
			redirect_updt(data->lst_cmd->ft_stdin, data->lst_cmd->ft_stdout);
			if (check_builtin(data->lst_cmd->argv[0]))
			{
				do_builtin(data, data->lst_cmd->argv[0]);
				close_pipes(data);
				free_all(data);
				exit(0);
			}
			path_cmd = execute_condition(data);
			if (!path_cmd)
				exit(g_exit_status);
			execute_execve(data, path_cmd);
		}
		data->lst_cmd = data->lst_cmd->next;
	}
}

static void	do_no_pipe(t_msh *data)
{
	char	*cmd;
	char	*path_cmd;

	cmd = data->lst_cmd->argv[0];
	data->pid[0] = fork();
	if (data->pid[0] == 0)
	{
		do_redir(data);
		redirect_updt(data->lst_cmd->ft_stdin, data->lst_cmd->ft_stdout);
		if (check_builtin(cmd))
		{
			do_builtin(data, cmd);
			free_all(data);
			exit(0);
		}
		path_cmd = execute_condition(data);
		if (!path_cmd)
			exit(g_exit_status);
		execute_execve(data, path_cmd);
	}
	if (check_builtin(cmd))
		exit_or_update_env(data, cmd);
}

void	do_execute(t_msh *data)
{
//	int		i;
	t_scom	*tmp_lstcmd;

	init_signal(1);
	tmp_lstcmd = data->lst_cmd;
	if (data->npipe > 0)
		do_multiples_pipe(data);
	else
		do_no_pipe(data);
//	i = -1;
	close_pipes(data);
//	while (++i < data->nscom)
//		waitpid(0, NULL, 0);
	get_exit_status(data);
	data->lst_cmd = tmp_lstcmd;
}
