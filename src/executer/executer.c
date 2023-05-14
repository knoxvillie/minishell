/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:00:11 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/14 20:03:25 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
//	if (abs_string_cmp(cmd, "echo"))
	if (abs_string_cmp(cmd, "cd"))
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
	printf("ola\n");
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

//void	do_execute(t_msh *data)
//{
//	char	*path_cmd;
//	pid_t	pid;
//	int		i;
//
//	i = 0;
//	if (data->npipe > 0)
//	{
//		while(data->lst_cmd)
//		{
//			pid = fork();
//			if (pid == 0)
//			{
//				//criar funcao para handle de todos os redir
//				do_redir(data->lst_cmd);
//				//fazer os dup e dup2 para conectar os processos pelos pipes.
//				//lembrar que o primeiro comando e o ultimo s'ao diferentes.
//				//no primeiro le do stdin e escreve no pipe
//				//o ultimo le do pipe e escreve no stdout
////			do_pipe(data->lst_cmd);
//				path_cmd = execute_condition(data); //alterar data para data->lst_cmd
//				if (!path_cmd)
//					return ;
//				execute_single_cmd(data, path_cmd); // alterar data para data->lst_cmd
//			}
//			data->lst_cmd = data->lst_cmd->next;
//		}
//	}
//	else
//	{
//		//execute_condition garante que o fork só sera feito para caso o comando não seja builtin
//		path_cmd = execute_condition(data);
//		if (!path_cmd)
//			return ;
//		pid = fork();
//		if (pid == 0)
//			execute_single_cmd(data, path_cmd);
//	}
//	while (i < data->nsCom)
//	{
//		waitpid(-1, NULL, 0);
//		i++;
//	}
//	free (path_cmd);
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
