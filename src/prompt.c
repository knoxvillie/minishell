/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:34:08 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/04 14:47:14 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

static void	s_manager_prompt(t_root *root)
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

static void	path_prompt(t_root *root)
{
	int		len_path;
	int		len_home;
	char	*tmp;

	len_path = (int)ft_strlen(root->p_path);
	len_home = (int)ft_strlen(root->home);
	if ((len_home == len_path) && !(ft_strncmp(root->home, root->p_path, len_home)))
	{
		free (root->p_path);
		root->p_path = ft_strdup("~");
		return ;
	}
	if ((len_home < len_path) && !(ft_strncmp(root->home, root->p_path, len_home)))
	{
		tmp = ft_substr(root->p_path, len_home, (len_path - len_home));
		free (root->p_path);
		root->p_path = ft_strjoin("~", tmp);
		free (tmp);
		return ;
	}
	if ((len_home > len_path) && !ft_strncmp(root->p_path, root->home, len_path))
		return ;
	free (root->p_path);
	root->p_path = NULL;
}

static void	prompt_prompt(t_root *root)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp1 = ft_strjoin(root->user, "@");
	tmp2 = ft_strjoin(root->s_manager, ":");
	tmp3 = ft_strjoin(tmp1, tmp2);
	free (tmp1);
	free (tmp2);
	tmp1 = ft_strjoin(root->p_path, "$ ");
	root->prompt = ft_strjoin(tmp3, tmp1);
	free (tmp3);
	free (tmp1);
}

char	*display_prompt(t_root *root)
{
	// user, s_manager and home only updates once.
	if (!root->n_exec)
	{
		root->user = get_value_from_key(root->list, "USER");
		root->s_manager = get_value_from_key(root->list, "SESSION_MANAGER");
		root->home = get_value_from_key(root->list, "HOME");
		s_manager_prompt(root);
	}
	root->p_path = getcwd(NULL, 0);
	path_prompt(root);
	if (!root->p_path)
		put_string_exit("Error: Path prompt is NULL\n", 1);
	prompt_prompt(root);
	return (root->prompt);
}