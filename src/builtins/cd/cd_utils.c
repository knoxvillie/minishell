/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 19:42:49 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/05/21 21:07:51 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*do_dot(t_msh *data)
{
	char	*arg;
	char	*pwd;
	char	*tmp;
	int		i;

	arg = data->lst_cmd->argv[1];
	pwd = get_value_from_key(data->ppt->list, "PWD");
	if (abs_string_cmp(arg, "."))
		return (pwd);
	if (abs_string_cmp(arg, ".."))
	{
		i = (int)ft_strlen(pwd);
		while (pwd[i] != '/')
			i--;
		if (i == 0)
			return (free (pwd), ft_strdup("/"));
		tmp = ft_substr(pwd, 0, i);
		return (free(pwd), tmp);
	}
	if (abs_string_cmp(arg, "-"))
		return (free (pwd), ft_strdup("-"));
	return (ft_strdup(arg));
}


//const char* dir = "C:/Users/apples";
//
//// Structure which would store the metadata
//struct stat sb;
//
//// Calls the function with path as argument
//// If the file/directory exists at the path returns 0
//// If block executes if path exists
//if (stat(dir, &sb) == 0)
//cout << "The path is valid!";
//else
//cout << "The Path is invalid!";