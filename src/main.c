/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:57:37 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/07 09:53:03 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

extern int	exit_status;

static t_msh	*init_data(t_msh *data, char **env)
{
	data->ppt = (t_ppt *)malloc(sizeof(t_ppt));
	data->lst_cmd = (t_sCom *)malloc(sizeof(t_sCom));
	env_to_list(data, env);
	return (data);
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
	data = init_data(data, env);
	while (1)
	{
		input = readline(display_prompt(data->ppt));
		if (!input || !*input)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			free (input);
			break ;
		}
        //Still needs leak check. next thing to do and some hardcore test.
        if (ft_parse(input, data))
        {
            //in case of error
            free (input);
            break ;
        }
//		do_execute(data);
		free (input);
	}
	free_over(data);
	return (0);
}
