/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintaxe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:09:22 by kfaustin          #+#    #+#             */
/*   Updated: 2023/04/29 18:59:00 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

// If ok true else false
/*bool	check_pipes(char *input)
{
	int		len;

	len = ft_strlen(input);
	if (*input == '|' || input[len - 1] == '|')
	{
		ft_putstr_fd("Error: Invalid pipes syntax", 2);
		return (false);
	}

}*/

static void	is_inside_quotes(char *ptr, char c)
{
	if ((c == '\'' || c == '\"') && !(*ptr))
		*ptr = c;
	else if (*ptr && (*ptr == c))
		*ptr = '\0';
}

static bool	putstr_fd_bool(char *str, int fd, bool status)
{
	ft_putstr_fd(str, fd);
	return (status);
}

bool	check_invalid_operator(char *input)
{
	char	inside_q;
	int		i;
	int		len;

	inside_q = '\0';
	i = -1;
	len = ft_strlen(input);
	while (input[++i])
	{
		is_inside_quotes(&inside_q, input[i]);
		if (!inside_q)
		{
			if (ft_strchr("&;(){}*\\", input[i]))
				putstr_fd_bool("Error: Invalid operators (&;(){}*\\)\n", 2, false);
			if (((i + 1) < len) && input[i] == '|' && input[i + 1] == '|')
				putstr_fd_bool("Error: Invalid operator (||)\n", 2, false);
			if (((i + 1) < len) && input[i] == '&' && input[i + 1] == '&')
				putstr_fd_bool("Error: Invalid operator (&&)\n", 2, false);

		}
	}
}

bool	check_unclosed_quotes(char *input)
{
	char	inside_q;

	inside_q = '\0';
	while (*input)
	{
		while (*input && !inside_q)
		{
			if (*input == '\'' || *input == '\"')
				inside_q = *input;
			input++;
		}
		while (*input && inside_q)
		{
			if (*input == inside_q)
				inside_q = '\0';
			input++;
		}
	}
	if (!inside_q)
		return (true);
	return (false);
}

// Be sure that input and *input is not false
bool	check_syntax_prompt(char *input)
{
	if (!check_unclosed_quotes(input))
	{
		ft_putstr_fd("Error: Unclosed quotes found\n", 2);
		return (false);
	}
	return (true);
}

/*
bool	check_unclosed_quotes(char *input)
{
	int		single_quotes;
	int		double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	while (*input)
	{
		if (*input== '\'')
			single_quotes++;
		else if (*input == '\"')
			double_quotes++;
		input++;
	}
	if ((single_quotes % 2 != 0) || (double_quotes % 2 != 0))
		return (true);
	return (false);
}*/

void    get_token(t_list **cTable, char **str) {
    t_sCom *sCom;
    char *tmp;

    tmp = *str;
    if (*tmp == '|')
        ola;
    else if (*tmp == '&')
        ola;
    else if (*tmp == ';')
        ola;
    else if (*tmp == '(')
        ola;
    else if (*tmp == ')')
        ola;
    else if (*tmp == '<')
        verificar
    se
    em
    seguida
    tem outro<;
    else if (*tmp == '>')
        verificar
    se
    em
    seguida
    tem
    outro > ;
    else if (*tmp == '\"')
        usar check_unclosed_quotes();
    else if (*tmp == '\'')
        usar check_unclosed_quotes();
    else
        while (**str && !ft_strchr(WSPACE, **str) && !ft_strchr(METACH, **str))
            (*str)++;
    return;
}

t_list  *parse(char	*input){
    t_list  *cTable;

    char *str;

    str = input;
    while (*str)
    {
        while (*str && ft_strchr(WSPACE, *str))
            str++;
        get_token(&cTable, &str);
    }
    return (cTable);
}


//create a function that read the input from main and create a linked list using the function from libft with each token.
// example: echo >redic "fabio valli" > redic2 vieira | ls -la kelvin | >redic1 echo kelvin fabio oil ola
//          WORD->REDIR->WORD->REDIR->WORD->PIPE->WORD->WORD->WORD->PIPE->REDIR->WORD->WORD->WORD->WORD->WORD->NULL