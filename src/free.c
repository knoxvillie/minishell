/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:17:07 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/18 21:57:47 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

void	free_all(t_msh *data)
{
	free_t_env(data->ppt->list);
	if (data->export->exp)
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

void	free_fd(t_msh *data)
{
	int i;

	i = 0;
	while (i < data->npipe)
	{
		free(data->fd[i]);
		i++;
	}
	free(data->fd);
}

/*void	free_over(t_msh *data)
{
	free_t_env(data->ppt->list);
	if (data->export->exp)
		free_t_exp(data->export->exp);
	free (data->export);
	free_table(data->env);
	free_prompt(data->ppt);
	free (data->ppt);
	free (data);
}*/

void	free_over(t_msh *data)
{
	free_t_env(data->ppt->list);
	if (data->export->exp)
		free_t_exp(data->export->exp);
	free (data->export);
	free_table(data->env);
	free_prompt(data->ppt);
	free (data->ppt);
	free_fd(data);
	//free_lstsCom(&(data->lst_cmd));
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
	free (root->abs_path);
}

void	free_table(char **table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	while(table[i])
	{
		free (table[i]);
		i++;
	}
	free (table);
}

void	free_t_exp(t_env *list)
{
	t_env	*env;

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

void	free_t_env(t_env *list)
{
	t_env	*header;

	while (list)
	{
		header = list->next;
		free (list->key);
		free (list->value);
		free (list);
		list = header;
	}
}
