/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:57:37 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/18 14:16:13 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

extern int	exit_status;

static void	do_minishell(t_msh *data)
{
	char	*input;

	while (true)
	{
		input = readline(display_prompt(data->ppt));
		if (input == NULL)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			free (input);
			break ;
		}
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		if (ft_parse(input, data))
		{
			free_lstsCom(&(data->lst_cmd));
			free (input);
			break ;
		}
		create_pipe(data);
		do_execute(data);
		free_lstsCom(&(data->lst_cmd));
		free (input);
		//close all pipes and free the **fd
	}
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
	signal(SIGQUIT, SIG_IGN);
	init_signal();
	do_minishell(data);
	free_over(data);
	return (0);
}
