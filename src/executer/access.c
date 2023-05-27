/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:51:46 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/27 18:38:30 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_execve(t_msh *data, char *path_cmd)
{
	char	**cmd;

	cmd = (char **)data->lst_cmd->argv;
	if (execve(path_cmd, cmd, data->env) < 0)
	{
		printf("msh: error on execve\n");
		exit(1);
	}
}

static char	*path_plus_cmd(char *path, char *cmd)
{
	char	*str;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	str = ft_strjoin(tmp, cmd);
	free (tmp);
	return (str);
}

char	*check_access(char *path, char *cmd)
{
	int		i;
	char	*str;
	char	**table_path;

	i = -1;
	table_path = ft_split(path, ':');
	while (table_path[++i])
	{
		str = path_plus_cmd(table_path[i], cmd);
		if (access(str, F_OK) == 0)
		{
			free_table(table_path);
			return (str);
		}
		free (str);
	}
	free_table(table_path);
	return (NULL);
}
