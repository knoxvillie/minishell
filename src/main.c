/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:57:37 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/08 16:07:59 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

extern int	exit_status;

void	free_over(t_msh *data)
{
	free_t_env(data->ppt->list);
	free_t_ppt(data->ppt);
	free (data->ppt);
	free (data->lst_cmd);
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

bool	main_loop(t_msh *data)
{
	char	*input;

	input = readline(display_prompt(data->ppt));
	if (*input == 'X')
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		free (input);
		return (false);
	}
	/*if (ft_parse(data, input))
	{
		free (input);
		return (false);
	}
	do_execute(data, input);*/
	printf("%s\n", input);
	free (input);
	return (true);
}

static void	init_data(t_msh *data, char **env)
{
	data->ppt = (t_ppt *)malloc(sizeof(t_ppt));
	data->ppt->n_exec = 0;
	data->ppt->path = NULL;
	data->ppt->prompt = NULL;
	data->lst_cmd = (t_sCom *)malloc(sizeof(t_sCom));
	env_to_list(data, env);
	//return (data);
}

int	main(int argc, char **argv, char **env)
{
	t_msh	*data;

	(void)argc;
	(void)argv;
	data = (t_msh *)malloc(sizeof(t_msh));
	init_data(data, env);
	//data = init_data(data, env);
	while (main_loop(data))
		;
	free_over(data);
	return (0);
}
