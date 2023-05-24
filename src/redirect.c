/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:26:11 by kfaustin          #+#    #+#             */
/*   Updated: 2023/05/24 14:29:16 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

void	do_heredoc(t_msh *data)
{
	int 	tmp_fd;
	char	*buff;
	t_list	*tmp;
	t_redir	*tmp_red;


	tmp = data->lst_cmd->lstofredirin;
	tmp_red = tmp->content;
	tmp_fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR);
	signal(SIGINT, SIG_DFL);
	if (tmp_fd < 0)
	{
		ft_putstr_fd("Error while opening file.\n", 2);
		free_all(data);
		exit(1);
	}
	while (1)
	{
		buff = readline(">");
		if (!buff)
		{
			ft_putstr_fd("msh: warning: here-doc at line 1 delimited by end-of-file\n", 2);
			break ;
		}
		buff[ft_strlen(buff)] = '\0';
		if (abs_string_cmp(tmp_red->filename, buff))
			break ;
		ft_putendl_fd(buff, tmp_fd);
		free(buff);
	}
	close(tmp_fd);
	free(buff);
	data->lst_cmd->ft_stdin = open(".heredoc",O_RDWR);
}

void	open_redir_in(t_msh *data)
{
	t_list	*tmp;
	t_redir	*tmp_red;

	tmp = data->lst_cmd->lstofredirin;
	while(tmp)
	{
		tmp_red = tmp->content;
		if (tmp_red->type == LESS)
		{
			data->lst_cmd->ft_stdin = open(tmp_red->filename,O_RDONLY);
			if (data->lst_cmd->ft_stdin < 0)
			{
				ft_putstr_fd("msh: ", 2);
				ft_putstr_fd(tmp_red->filename, 2);
				ft_putstr_fd(": no such file or directory\n", 2);
				free_all(data);
				exit(1);
			}
		}
		else if (tmp_red->type == LESSLESS)
		{
			do_heredoc(data);
		}
		tmp = tmp->next;
	}
}

void	open_redir_out(t_msh *data)
{
	t_list	*tmp;
	t_redir	*tmp_red;

	tmp = data->lst_cmd->lstofredirout;
	while(tmp)
	{
		tmp_red = tmp->content;
		if (tmp_red->type == GREAT)
		{
			data->lst_cmd->ft_stdout = open(tmp_red->filename,O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
			if (data->lst_cmd->ft_stdout < 0)
			{
				ft_putstr_fd("Error while opening file.\n", 2);
				free_all(data);
				exit(1);
			}
		}
		else if (tmp_red->type == GREATGREAT)
		{
			data->lst_cmd->ft_stdout = open(tmp_red->filename,O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
			if (data->lst_cmd->ft_stdout < 0)
			{
				ft_putstr_fd("Error while opening file.\n", 2);
				free_all(data);
				exit(1);
			}
		}
		tmp = tmp->next;
	}
}

