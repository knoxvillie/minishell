/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dobuiltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:32:55 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/24 14:35:06 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

void	exit_or_update_env(t_msh *data, char *cmd)
{
	if (abs_string_cmp(cmd, "cd"))
		return (builtin_cd_update(data));
	if (abs_string_cmp(cmd, "export"))
		return (builtin_export_update(data));
	if (abs_string_cmp(cmd, "unset"))
		return (builtin_unset_update(data));
	if (abs_string_cmp(cmd, "exit"))
		return (builtin_exit_update(data));
}

void	do_builtin(t_msh *data, char *cmd)
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