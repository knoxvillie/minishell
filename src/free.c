/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:17:07 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/24 11:09:15 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

void	free_all(t_msh *data)
{
	free_t_env(data->ppt->list);
	free_t_exp(data->export->exp);
	free (data->export);
	free_table(data->env);
	free_prompt(data->ppt);
	free (data->ppt);
	free_fd(data);
	free_lstsCom(data);
	close_pipes(data);
	free (data);
	unlink(".heredoc");
}

void	free_over(t_msh *data)
{
	free_t_env(data->ppt->list);
	free_t_exp(data->export->exp);
	free (data->export);
	free_table(data->env);
	free_prompt(data->ppt);
	free (data->ppt);
	free_fd(data);
	close_pipes(data);
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

void	free_t_exp(t_env *list)
{
	t_env	*env;

	if (list == NULL)
		return ;
	while (list)
	{
		free(list->key);
		if (list->value != NULL)
			free (list->value);
		env = list->next;
		free(list);
		list = env;
	}
}
