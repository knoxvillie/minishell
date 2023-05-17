/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:57:37 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/17 15:29:04 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

extern int	exit_status;

void	free_over(t_msh *data)
{
	free_t_env(data->ppt->list);
	if (data->export->exp)
		free_t_exp(data->export->exp);
	free (data->export);
	free_table(data->env);
	free_t_ppt(data->ppt);
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

void	init_export_env(t_msh *data)
{
	data->export = (t_exp *)malloc(sizeof(t_exp));
	data->export->env = data->ppt->list;
	data->export->exp = NULL;
	if (!data->export)
		put_string_exit("Error: Malloc of data->export failed\n", 1);
}

static t_msh	*init_data(t_msh *data, char **env)
{
	data->ppt = (t_ppt *)malloc(sizeof(t_ppt));
	data->ppt->n_exec = 0;
	data->ppt->path = NULL;
	data->ppt->prompt = NULL;
	data->ppt->abs_path = NULL;
	data->npipe = 0;
	data->nsCom = 0;
	data->fd = NULL;
	data->export = NULL;
	env_to_list(data, env);
	init_export_env(data);
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
/*		==287403== 0 bytes in 11 blocks are definitely lost in loss record 1 of 67
																				==287403==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
																											==287403==    by 0x402402: create_pipe (create_pipe.c:24)
		==287403==    by 0x4019CE: main_loop (main.c:84)
		==287403==    by 0x40183A: main (main.c:102)
		==287403==
		  ==287403== 1 bytes in 1 blocks are definitely lost in loss record 3 of 67
																				 ==287403==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
																											 ==287403==    by 0x405789: ft_strdup (in /nfs/homes/kfaustin/Desktop/minishell/minishell)
																																		==287403==    by 0x403BCC: get_token_word (parser_utils.c:255)
		==287403==    by 0x402F0D: get_token (parser.c:101)
		==287403==    by 0x40313F: ft_parse (parser.c:168)
		==287403==    by 0x40199D: main_loop (main.c:78)
		==287403==    by 0x40183A: main (main.c:102)*/
        free_lstsCom(&(data->lst_cmd));
        free (input);
        return (true);
	}
	create_pipe(data);
	do_execute(data);
	free_lstsCom(&(data->lst_cmd));
	free (input);
	//close all pipes
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
