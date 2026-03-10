/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:13:11 by nofelten          #+#    #+#             */
/*   Updated: 2026/03/10 14:56:06 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
//Free the token struct list and all is contents
*/
void	free_list_token(t_token **list)
{
	t_token	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->str);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}

/*
//Add the new node at the end of the token struct list
*/
size_t	list_add_back_token(t_token **list, t_token *new_elem,
			char *input, int idx)
{
	t_token	*current;
	size_t	len;

	if (!list || !new_elem)
		return (0);
	len = strlen_token(input, idx);
	if (!*list)
		*list = new_elem;
	else
	{
		current = *list;
		while (current->next)
			current = current->next;
		current->next = new_elem;
	}
	return (len);
}

/*
//Creates a new node of the token struct list and fill it (char *, type, state)
*/
t_token	*create_one_token(t_shell *shell, char *input, size_t idx)
{
	t_token	*new;
	size_t	len;
	char	*tmp;

	if ((input[idx] == '\'' || input[idx] == '\"') && !is_quoted(input, idx))
		return (NULL);
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	len = strlen_token(input, idx);
	new->str = ft_strndup(&input[idx], len);
	if (!new->str)
		return (free(new), NULL);
	tmp = expander(shell, new->str);
	free(new->str);
	new->str = tmp;
	new->str = remove_quotes(new->str, 0, 0);
	new->state = get_state_token(input[idx], is_quoted(input, idx));
	if (new->state == GENERAL)
		new->type = get_type_token(new->str);
	else
		new->type = WORD;
	new->next = NULL;
	return (new);
}
