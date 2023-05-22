/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:34:08 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/18 11:01:34 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	s_manager_prompt(t_ppt *root)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (root->s_manager[i] != '/')
		i++;
	j = 0;
	while (root->s_manager[j] != '.' && root->s_manager[j] != ':')
		j++;
	tmp = ft_substr(root->s_manager, (i + 1), (j - (i + 1)));
	free (root->s_manager);
	root->s_manager = tmp;
}

static void	path_prompt(t_ppt *root)
{
	int		len_p;
	int		len_h;
	char	*tmp;

	len_p = (int)ft_strlen(root->path);
	len_h = (int)ft_strlen(root->home);
	if ((len_h == len_p) && !(ft_strncmp(root->home, root->path, len_h)))
	{
		free (root->path);
		root->path = ft_strdup("~");
		return ;
	}
	if ((len_h < len_p) && !(ft_strncmp(root->home, root->path, len_h)))
	{
		tmp = ft_substr(root->path, len_h, (len_p - len_h));
		free (root->path);
		root->path = ft_strjoin("~", tmp);
		free (tmp);
		return ;
	}
	if ((len_h > len_p) && !ft_strncmp(root->path, root->home, len_p))
		return ;
	free (root->path);
	root->path = NULL;
}

static void	prompt_prompt(t_ppt *root)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	free (root->prompt);
	tmp1 = ft_strjoin(root->user, "@");
	tmp2 = ft_strjoin(root->s_manager, ":");
	tmp3 = ft_strjoin(tmp1, tmp2);
	free (tmp1);
	free (tmp2);
	tmp1 = ft_strjoin(root->path, "$ ");
	root->prompt = ft_strjoin(tmp3, tmp1);
	free (tmp3);
	free (tmp1);
}

char	*display_prompt(t_ppt *root)
{
	if (root->n_exec == 0)
	{
		root->user = get_value_from_key(root->list, "USER");
		root->s_manager = get_value_from_key(root->list, "SESSION_MANAGER");
		root->home = get_value_from_key(root->list, "HOME");
		s_manager_prompt(root);
	}
	free (root->path);
	root->path = getcwd(NULL, 0);
	path_prompt(root);
	if (!root->path)
		put_str_exit("Error: Path prompt is NULL\n", 1);
	prompt_prompt(root);
	root->n_exec++;
	return (root->prompt);
}
