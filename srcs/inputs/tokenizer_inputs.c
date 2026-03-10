/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_inputs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:13:11 by nofelten          #+#    #+#             */
/*   Updated: 2026/03/10 16:40:21 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
//Return the size_t of the current token
*/
size_t	strlen_token(char *input, size_t idx)
{
	size_t	len;
	int		quote;

	len = 0;
	quote = 0;
	if (input[idx] && is_separator(input[idx], NO))
	{
		quote = input[idx];
		while (input[len + idx] == quote && len < 2)
			len++;
		return (len);
	}
	while (input[len + idx])
	{
		if ((input[len + idx] == '\'' || input[len + idx] == '\"') && !quote)
			quote = input[len + idx];
		else if (quote && input[len + idx] == quote)
			quote = 0;
		else if (!quote && is_separator(input[len + idx], NO))
			break ;
		len++;
	}
	return (len);
}

/*
//Return the type of the current token (WORD, PIPE etc..)
*/
t_tok_type	get_type_token(char *str)
{
	if (!str)
		return (WORD);
	if (ft_strncmp("<<", str, 3) == 0)
		return (DELIMITER);
	if (ft_strncmp(">>", str, 3) == 0)
		return (APPEND);
	if (ft_strncmp("|", str, 2) == 0)
		return (PIPE);
	if (ft_strncmp("<", str, 2) == 0)
		return (HERE_IN);
	if (ft_strncmp(">", str, 2) == 0)
		return (HERE_OUT);
	return (WORD);
}

/*
//Return the state of the current token (IN_SQUOTE, GENERAL etc..)
*/
t_tok_state	get_state_token(char c, int quoted)
{
	if (quoted)
	{
		if (c == '\'')
			return (IN_SQUOTE);
		if (c == '\"')
			return (IN_DQUOTE);
	}
	return (GENERAL);
}

/*
//Get input by user, parse it and create token struct list
*/
t_token	*tokenizer(t_shell *shell, size_t i, char *input, t_token **list)
{
	t_token	*new;
	size_t	len_input;

	len_input = ft_strlen(input);
	while (input && input[i] && i < len_input)
	{
		while (i < len_input && ft_isspace(input[i]))
			i++;
		if (i == len_input || !input[i])
			break ;
		new = create_one_token(shell, input, i);
		if (!new)
			return (write(2, "minishell: syntax error: unclosed quote\n", 40),
				free_list_token(list), NULL);
		if (new->str && new->str[0] == '\0' && !is_quoted(input, i))
		{
			i += strlen_token(input, i);
			free(new->str);
			free(new);
			continue ;
		}
		i += list_add_back_token(list, new, input, i);
	}
	return (*list);
}
