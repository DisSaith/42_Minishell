/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:13:11 by nofelten          #+#    #+#             */
/*   Updated: 2026/03/09 08:59:34 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
//Check and return 1 if it's a redirection (|, >, >>, <, <<), or 0
*/
int	is_redirection(t_token *token)
{
	if (token->type == HERE_IN
		|| token->type == HERE_OUT
		|| token->type == DELIMITER
		|| token->type == APPEND)
		return (1);
	return (0);
}

/*
//Check and return 1 if char *input is_quoted (" or '), 0 otherwise
*/
int	is_quoted(char *input, size_t idx)
{
	size_t	i;
	char	quote;

	if (!input)
		return (0);
	i = idx;
	quote = input[i];
	if (quote != '\'' && quote != '\"')
		return (0);
	i = idx + 1;
	while (input[i] && input[i] != quote)
		i++;
	if (input[i] == quote)
		return (1);
	return (0);
}

/*
//Check if it's an separator or not
*/
int	is_separator(char c, int quote)
{
	if (quote)
		return (0);
	if (ft_isspace(c) || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

/*
//Error message if the syntax of the user's input is wrong
*/
int	error_syntax_token(char *token)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	write(2, token, ft_strlen(token));
	write(2, "'\n", 2);
	return (2);
}

/*
//Check the syntax of the token struct list before the parsing fonction
*/
int	check_syntax_token(t_shell *shell, t_token *list)
{
	t_token	*cur;

	cur = list;
	if (cur && cur->type == PIPE)
		return (error_syntax_token(cur->str));
	while (cur)
	{
		if (cur->type == DELIMITER)
			shell->nbr_heredocs++;
		if (cur->type == PIPE && (!cur->next || cur->next->type == PIPE))
			return (error_syntax_token(cur->str));
		if (ft_strncmp("||", cur->str, 3) == 0)
			return (error_syntax_token("|"));
		if (cur->type == HERE_IN || cur->type == HERE_OUT
			|| cur->type == DELIMITER || cur->type == APPEND)
		{
			if (!cur->next)
				return (error_syntax_token("newline"));
			if (cur->next->type != WORD)
				return (error_syntax_token(cur->next->str));
		}
		cur = cur->next;
	}
	return (1);
}
