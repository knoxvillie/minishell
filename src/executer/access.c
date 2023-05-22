/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:51:46 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/22 21:37:34 by fvalli-v         ###   ########.fr       */
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
