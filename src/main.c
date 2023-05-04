/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:57:37 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/04 14:32:18 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	exit_status;

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_root	root;
	t_env	*header;

	(void)argc;
	(void)argv;
	(void)env;
	(void)input;
	(void)header;

	env_to_list(&root, env);
	root.prompt = NULL;
	root.n_exec = 0;
	/*while (1)
	{
		input = readline(display_prompt(&root));
		if (!input)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			free (input);
			break ;
		}
		if (!(*input))
		{
			printf("%s", input);
			continue ;
		}
		printf("%s\n", input);
		free (input);
		free (root.path);
	}*/
	header = root.list;
	while (root.list)
	{
		printf("%s - %s\n", root.list->key, root.list->value);
		root.list = root.list->next;
	}
	root.list = header;
	//builtin_unset(root.list, "OUTRAVAR");
	//printf("\n\n\n UNSET\n");
	printf("\n\n\n PULANDO LINHAS \n");
	builtin_export(&root, "CAVaLO = ");
	while (root.list)
	{
		printf("%s - %s\n", root.list->key, root.list->value);
		root.list = root.list->next;
	}
	root.list = header;
	free_t_env(root.list);
	//free_t_root(&root);
	return (0);
}
