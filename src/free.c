/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:17:07 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/27 14:17:12 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

void	free_all(t_msh *data)
{
	free(data->pid);
	free_t_env(data->ppt->list);
	free_t_exp(data->export->exp);
	free (data->export);
	free_table(data->env);
	free_prompt(data->ppt);
	free (data->ppt);
	close_pipes(data);
	free_fd(data);
	free_lstsCom(data);
	free (data);
	unlink(".heredoc");
}

void	free_fork(t_msh *data)
{
	free(data->pid);
	free_t_env(data->ppt->list);
	free_t_exp(data->export->exp);
	free (data->export);
	free_table(data->env);
	free_prompt(data->ppt);
	free (data->ppt);
	free_fd(data);
	free_lstsCom(data);
	free (data);
	unlink(".heredoc");
}

void	free_over(t_msh *data)
{
	free(data->pid);
	free_t_env(data->ppt->list);
	free_t_exp(data->export->exp);
	free (data->export);
	free_table(data->env);
	free_prompt(data->ppt);
	free (data->ppt);
	close_pipes(data);
	free_fd(data);
	free (data);
	unlink(".heredoc");
}

void	free_prompt(t_ppt *root)
{
	free (root->prompt);
	free (root->user);
	free (root->s_manager);
	free (root->home);
	free (root->path);
}

void	free_table(char **table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	while (table[i])
	{
		free (table[i]);
		i++;
	}
	free (table);
}
