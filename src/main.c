/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:57:37 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/21 13:19:04 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

int	exit_status = 0;

static void	do_minishell(t_msh *data)
{
	char	*input;
	char	*trim;

	while (true)
	{
		init_signal(0);
		input = readline(display_prompt(data->ppt));
		if (input == NULL)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			free (input);
			break ;
		}
		trim = ft_strtrim(input, WSPACE);
		if (*trim == '\0')
		{
			free(input);
			free(trim);
			continue ;
		}
		if (!ft_strchr(WSPACE, *input))
			add_history(input);
		free(input);
		if (ft_parse(trim, data))
		{
			free_lstsCom(data);
			free (trim);
			break ;
		}
		create_pipe(data);
		do_execute(data);
		free_lstsCom(data);
		free (trim);
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
	do_minishell(data);
	free_over(data);
	return (0);
}
