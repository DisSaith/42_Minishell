/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:13:11 by nofelten          #+#    #+#             */
/*   Updated: 2026/03/09 08:57:02 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
//Count and return the number of commands
*/
int	count_nbr_cmds(t_shell *shell)
{
	t_cmd	*current;
	int		count;

	if (!shell->cmds)
		return (0);
	current = shell->cmds;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

/*
//Count and return the number of arguments for one command
*/
size_t	get_nbr_args_one_cmd(t_token *start_cmd)
{
	t_token	*current;
	size_t	i;
	size_t	skip_next;

	if (!start_cmd)
		return (0);
	current = start_cmd;
	i = 0;
	skip_next = 0;
	while (current && current->type != PIPE)
	{
		if (is_redirection(current))
			skip_next = 1;
		if (current->type == WORD && !skip_next)
			i++;
		else if (current->type == WORD && skip_next)
			skip_next = 0;
		current = current->next;
	}
	return (i);
}

/*
//Fill char **cmd_args of one node of cmd the struct list
*/
int	fill_cmd_args(t_token *start_cmd, char **cmd_args, size_t nbr_args)
{
	size_t	i;
	int		skip_next;

	if (!start_cmd)
		return (0);
	i = 0;
	skip_next = 0;
	while (i < nbr_args && start_cmd && start_cmd->type != PIPE)
	{
		if (is_redirection(start_cmd))
			skip_next = 1;
		if (start_cmd->type == WORD && !skip_next)
		{
			cmd_args[i] = ft_strdup(start_cmd->str);
			if (!cmd_args[i])
				return (0);
			i++;
		}
		else if (start_cmd->type == WORD && skip_next)
			skip_next = 0;
		start_cmd = start_cmd->next;
	}
	cmd_args[i] = NULL;
	return (1);
}

/*
//Parse and create the cmd struct list based on the token struct list
*/
t_cmd	*parsing(t_token *list, t_shell *shell)
{
	t_token	*current;
	t_token	*start_cmd;
	t_cmd	*new;
	ssize_t	nbr_args;

	if (!list || check_syntax_token(shell, list) != 1)
	{
		shell->exit_status = 2;
		return (NULL);
	}
	current = list;
	while (current)
	{
		start_cmd = current;
		nbr_args = get_nbr_args_one_cmd(start_cmd);
		while (current && current->type != PIPE)
			current = current->next;
		new = create_one_cmd(shell, start_cmd, nbr_args);
		list_add_back_cmd(&shell->cmds, new);
		if (current && current->type == PIPE)
			current = current->next;
	}
	return (shell->cmds);
}
