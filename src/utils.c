/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:12:39 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/12 19:19:09 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	put_string_exit(char *str, int flag)
{
	ft_putstr_fd(str, 2);
	exit(flag);
}

void	free_t_env(t_env *list)
{
	t_env *header;

	while (list)
	{
		header = list->next;
		free (list->key);
		free (list->value);
		free (list);
		list = header;
	}
}

void	free_t_ppt(t_ppt *root)
{
	free (root->prompt);
	free (root->user);
	free (root->s_manager);
	free (root->home);
	free (root->path);
	free (root->abs_path);
}

bool	abs_string_cmp(char *s1, char *s2)
{
	int		len_s1;
	int		len_s2;

	len_s1 = (int)ft_strlen(s1);
	len_s2 = (int) ft_strlen(s2);
	if ((len_s1 == len_s2) && !ft_strncmp(s1, s2, len_s1))
		return (true);
	return (false);
}

void	free_table(char **table)
{
	int	i;

	i = 0;
	while (table[i])
	{
		free (table[i]);
		i++;
	}
	free (table);
}

int	size_of_list(t_env *lst)
{
	int		size;
	t_env	*tmp;

	size = 0;
	tmp = lst;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
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
		data->env[i] = (char *)malloc(sizeof(char)
				* (ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2));
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
