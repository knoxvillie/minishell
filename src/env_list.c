/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:27:09 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/05 16:14:11 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_key_value(char **key, char **value, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	*key = ft_substr(str, 0, i);
	*value = ft_substr(str, (i + 1), ft_strlen(str) - i);
}

void	init_env_node(t_env **node, char *key, char *value)
{
	*node = (t_env *)malloc(sizeof(t_env));
	if (!(*node))
		put_string_exit("Error: Malloc of *node fails\n", 1);
	(*node)->key = key;
	(*node)->value = value;
	(*node)->next = NULL;
}

void	stack_env_list(t_ppt *root, t_env *node)
{
	t_env	*header;

	(void)header;
	header = root->list;
	if (!root->list)
	{
		root->list = node;
		return ;
	}
	while (root->list->next)
		root->list = root->list->next;
	root->list->next = node;
	//root->list = header;
}

void	env_to_list(t_ppt *root, char **env)
{
	int		i;
	char	*key;
	char	*value;
	t_env	*node;

	if (!env)
		put_string_exit("Error: env is NULL\n", 1);
	i = -1;
	root = (t_ppt *)malloc(sizeof(t_ppt));
	while (env[++i])
	{
		init_key_value(&key, &value, env[i]);
		init_env_node(&node, key, value);
		stack_env_list(root, node);
	}
}