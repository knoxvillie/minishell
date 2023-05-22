/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:51:46 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/18 15:09:34 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*path_plus_cmd(char *path, char *cmd)
{
	char	*str;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	str = ft_strjoin(tmp, cmd);
	free (tmp);
	return (str);
}

static char	*check_access_continue(char *path, char *cmd)
{
	int		i;
	char	*str;
	char	**table_path;

	if (access(cmd, F_OK) == 0)
		return (cmd);
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

char	*check_access(t_msh *data, char *cmd)
{
	char	*str;
	char	*path;

	path = get_value_from_key(data->ppt->list, "PATH");
	if (!path)
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		return (NULL);
	}
	str = check_access_continue(path, cmd);
	free (path);
	if (!str)
		return (NULL);
	return (str);
}