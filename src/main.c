/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:57:37 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/24 14:01:44 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

int g_exit_status;

/* Returns -1 to continue, 0 to break, 1 to do nothing */
static int	do_trim_parser(t_msh *data, char *input, char **trim)
{
	if (input == NULL)
	{
		ft_putstr_fd("exit\n", 2);
		return (free (input), 0);
	}
	*trim = ft_strtrim(input, WSPACE);
	if (*(*trim) == '\0')
		return (free(input), free(*trim), -1);
	if (!ft_strchr(WSPACE, *input))
		add_history(input);
	free(input);
	if (ft_parse(*trim, data))
	{
		free_lstsCom(data);
		free (*trim);
		return (0);
	}
	return (1);
}

static void	do_minishell(t_msh *data)
{
	int		flag_dtp;
	char	*input;
	char	*trim;

	while (true)
	{
		init_signal(0);
		input = readline(display_prompt(data->ppt));
		flag_dtp = do_trim_parser(data, input, &trim);
		if (flag_dtp < 0)
			continue ;
		if (flag_dtp == 0)
			break ;
		create_pipe(data);
		do_execute(data);
		free_lstsCom(data);
		//free_fd(data);
		free (trim);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_msh	*data;

	if (argc > 1)
		return (ft_putstr_fd("msh: invalid number of arguments\n", 2), 1);
	(void) argv;
	data = (t_msh *)malloc(sizeof(t_msh));
	data = (t_msh *)ft_memset(data, 0, sizeof(t_msh));
	data = init_data(data, env);
	rl_clear_history();
	signal(SIGQUIT, SIG_IGN);
	do_minishell(data);
	free_over(data);
	return (0);
}
