/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:13:59 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/22 14:37:21 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_export_env(t_msh *data)
{
	data->export = (t_exp *)malloc(sizeof(t_exp));
	data->export->env = data->ppt->list;
	data->export->exp = NULL;
	if (!data->export)
		put_str_exit("Error: Malloc of data->export failed\n", 1);
}

t_msh	*init_data(t_msh *data, char **env)
{
	data->ppt = (t_ppt *)malloc(sizeof(t_ppt));
	data->ppt->n_exec = 0;
	data->ppt->path = NULL;
	data->ppt->prompt = NULL;
	data->npipe = 0;
	data->nscom = 0;
	data->fd = NULL;
	data->export = NULL;
	env_to_list(data, env);
	init_export_env(data);
	init_env_table(data);
	return (data);
}

static void	init_env_table_complement(t_msh *data, t_env *tmp)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (tmp)
	{
		j = -1;
		data->env[i] = malloc(sizeof(char) * (ft_strlen(tmp->key)
					+ ft_strlen(tmp->value) + 2));
		while (tmp->key[++j])
			data->env[i][j] = tmp->key[j];
		data->env[i][j++] = '=';
		k = 0;
		while (tmp->value[k])
			data->env[i][j++] = tmp->value[k++];
		data->env[i][j] = '\0';
		tmp = tmp->next;
		i++;
	}
	data->env[i] = NULL;
}

void	init_env_table(t_msh *data)
{
	t_env	*tmp;

	data->env = (char **)malloc(sizeof(char *)
			* (size_of_list(data->ppt->list) + 1));
	if (!data->env)
	{
		ft_putstr_fd("Error: Env table malloc failed\n", 2);
		return ;
	}
	tmp = data->ppt->list;
	init_env_table_complement(data, tmp);
}
