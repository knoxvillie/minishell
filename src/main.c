/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:57:37 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/05 16:04:30 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	exit_status;

void	init_data(t_msh *data, char **env)
{
	env_to_list(data->ppt, env);
}

void	free_over(t_msh *data)
{
	free_t_env(data->ppt->list);
	free_t_ppt(data->ppt);
	free (data);
}

void	printf_env(t_env *env)
{
	while (env)
	{
		printf("%s - %s\n", env->key, env->value);
		env = env->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_msh	*data;

	(void)argc;
	(void)argv;
	data = (t_msh *)malloc(sizeof(t_msh));
	data = (t_msh *)ft_memset(data, 0, sizeof(t_msh));
	init_data(data, env);
	while (1)
	{
		input = readline(display_prompt(data->ppt));
		if (!input || !*input)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			free (input);
			break ;
		}
		do_execute(data);
		free (input);
	}
	free_over(data);
	return (0);
}
