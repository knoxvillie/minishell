/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:27:09 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/22 14:40:04 by kfaustin         ###   ########.fr       */
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

t_env	*init_env_node(char *key, char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		put_str_exit("Error: Malloc of *node fails\n", 1);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_env	*stack_env_list(t_env *var, t_env *node)
{
	t_env	*header;

	header = var;
	if (var == NULL)
		return (node);
	while (var->next != NULL)
		var = var->next;
	var->next = node;
	return (header);
}

t_msh	*env_to_list(t_msh *data, char **env)
{
	int		i;
	char	*key;
	char	*value;
	t_env	*node;

	if (!env)
		put_str_exit("Error: env is NULL\n", 1);
	i = -1;
	data->ppt->list = NULL;
	while (env[++i])
	{
		init_key_value(&key, &value, env[i]);
		node = init_env_node(key, value);
		data->ppt->list = stack_env_list(data->ppt->list, node);
	}
	return (data);
}
