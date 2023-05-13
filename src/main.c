/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:57:37 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/13 10:19:10 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

extern int	exit_status;

void	free_over(t_msh *data)
{
	free_t_env(data->ppt->list);
	free_t_ppt(data->ppt);
	free_table(data->env);
	free (data->ppt);
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

static t_msh	*init_data(t_msh *data, char **env)
{
	data->ppt = (t_ppt *)malloc(sizeof(t_ppt));
	data->ppt->n_exec = 0;
	data->ppt->path = NULL;
	data->ppt->prompt = NULL;
	data->ppt->abs_path = NULL;
	env_to_list(data, env);
	init_env_table(data);
	return (data);
}

static bool	main_loop(t_msh *data)
{
	char	*input;

	input = readline(display_prompt(data->ppt));
	if (!input || !*input)
	{
		rl_clear_history();
		ft_putstr_fd("exit\nexit\n", STDOUT_FILENO);
		free (input);
		return (false);
	}
	add_history(input);
	if (ft_parse(input, data))
	{
		free (input);
		return (false);
	}
	do_execute(data);
	free_table(data->lst_cmd->argList);
	free_lstsCom(&(data->lst_cmd));
	free (input);
	return (true);
}

int main(int argc, char **argv, char **env)
{
	t_msh *data;

	(void) argc;
	(void) argv;
	data = (t_msh *) malloc(sizeof(t_msh));
	data = (t_msh *) ft_memset(data, 0, sizeof(t_msh));
	data = init_data(data, env);
	rl_clear_history();
	while (main_loop(data));
	free_over(data);
	return (0);
}
