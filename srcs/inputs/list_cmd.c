/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:13:11 by nofelten          #+#    #+#             */
/*   Updated: 2026/03/09 14:58:31 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
//Free cmd struct list and every content inside
*/
void	free_list_cmd(t_cmd **list)
{
	t_cmd	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		close_fd_cmd(*list);
		(*list)->cmd_args = free_tab_tab((*list)->cmd_args);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}

/*
//Add a new node at the end of cmd struct list
*/
void	list_add_back_cmd(t_cmd **list, t_cmd *new_elem)
{
	t_cmd	*current;

	if (!list || !new_elem)
		return ;
	if (!*list)
	{
		*list = new_elem;
		return ;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new_elem;
}

void	close_fd_cmd(t_cmd *cmd)
{
	if (cmd->in > 2)
		close(cmd->in);
	if (cmd->out > 2)
		close(cmd->out);
}

/*
//Creates a new node of cmd struct list (fll char **cmd_args and in/out)
*/
t_cmd	*create_one_cmd(t_shell *shell, t_token *start_cmd, size_t nbr_args)
{
	t_cmd	*new;

	if (!start_cmd || !start_cmd->str)
		return (NULL);
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	shell->current = new;
	new->out = -2;
	new->in = -2;
	get_redirection_cmd(shell, start_cmd, &new->in, &new->out);
	new->next = NULL;
	if (nbr_args == 0)
		return (close_fd_cmd(new), free(new), NULL);
	new->cmd_args = malloc(sizeof(char *) * (nbr_args + 1));
	if (!new->cmd_args)
		return (close_fd_cmd(new), free(new), NULL);
	if (!fill_cmd_args(start_cmd, new->cmd_args, nbr_args))
		return (close_fd_cmd(new), free_tab_tab(new->cmd_args),
			free(new), NULL);
	return (new);
}
