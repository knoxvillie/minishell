/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:12:39 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/11 15:19:02 by kfaustin         ###   ########.fr       */
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
	while(table[i])
	{
		free (table[i]);
		i++;
	}
	free (table);
}

/*int		size_of_list(t_env *node)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = node;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	update_env_table(t_msh *data)
{

}*/
