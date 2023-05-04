/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:51:46 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/04 15:56:33 by kfaustin         ###   ########.fr       */
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

static char	*check_access_continue(char **table_path, char *cmd)
{
	int		i;
	char	*str;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	i = 0;
	while (table_path[i])
	{
		str = path_plus_cmd(table_path[i], cmd);
		if (access(str, F_OK) == 0)
			return (str); // You have to free the str.
		free (str);
	}
	return (NULL);

}

// Fuc prototype may change when the parser is done
char	*check_access(t_root *root, char *cmd)
{
	int		i;
	char	*str;
	char	*path;
	char	**table_path;

	i = -1;
	path = get_value_from_key(root->list, "PATH");
	if (!path)
	{
		printf("minishell: %s: No such file or directory", cmd); //CHANGE
		return (NULL);
	}
	if (access(cmd, X_OK) == 0)
		return (cmd);
	table_path = ft_split(path, ':');
	free (path);
	while (table_path[++i])
	{
		str = path_plus_cmd(table_path[i], cmd);
		if (access(str, F_OK) == 0)
			return (str);
		free (str);
	}

	return (NULL);
}