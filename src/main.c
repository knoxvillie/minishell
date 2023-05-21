/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:57:37 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/21 09:02:57 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

extern int	exit_status;

static void	do_minishell(t_msh *data)
{
	char	*input;
	char	*trim;

	while (true)
	{
		input = readline(display_prompt(data->ppt));
		if (input == NULL) //-> ctrl + D
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			free (input);
			break ;
		}
		trim = ft_strtrim(input, " ");
		free(input);
		input = ft_strdup(trim);
		free(trim);
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		if (ft_parse(input, data))
		{
			free_lstsCom(data);
			free (input);
			break ;
		}
		create_pipe(data);
		do_execute(data);
		free_lstsCom(data);
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
