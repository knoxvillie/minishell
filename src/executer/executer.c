/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:00:11 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/08 15:17:05 by kfaustin         ###   ########.fr       */
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

bool	check_builtin(char *cmd)
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

static void	execute_single_cmd(t_msh *data, char *path_cmd, char **var)
{
	(void)data;
	//signals and redirect is handle here
	//if(check_builtin(data->lst_cmd->argList[0])) > Check is builtin
	execve(path_cmd, var, NULL);
}

void	do_execute(t_msh *data, char *input)
{
	char	*path_cmd;
	char	**var;
	pid_t	pid;

	var = ft_split(input, ' ');
	path_cmd = check_access(data, var[0]);
	if (!path_cmd)
		return ;
	pid = fork();
	if (pid == 0)
		execute_single_cmd(data, path_cmd, var);
	waitpid(pid, NULL, 0);
	free (path_cmd);
}
