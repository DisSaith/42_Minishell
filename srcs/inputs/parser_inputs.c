/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:13:11 by nofelten          #+#    #+#             */
/*   Updated: 2026/03/10 16:27:22 by acohaut          ###   ########.fr       */
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
size_t	get_nbr_args_one_cmd(t_token *start_cmd, size_t count)
{
	t_token	*current;
	char	**tmp_split;
	int		j;

	current = start_cmd;
	while (current && current->type != PIPE)
	{
		if (is_redirection(current))
			current = current->next;
		else if (current->type == WORD)
		{
			tmp_split = ft_split(current->str, ' ');
			j = 0;
			while (tmp_split && tmp_split[j])
			{
				count++;
				free(tmp_split[j++]);
			}
			free(tmp_split);
		}
		if (current)
			current = current->next;
	}
	return (count);
}

/*
//Restore spaces
*/
char	*rest_sp(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\1')
			str[i] = ' ';
		i++;
	}
	return (str);
}

/*
//Fill char **cmd_args of one node of cmd the struct list
*/
int	fill_cmd_args(t_token *start_cmd, char **cmd_args)
{
	size_t	i;
	int		j;
	char	**split_res;

	i = 0;
	while (start_cmd && start_cmd->type != PIPE)
	{
		if (is_redirection(start_cmd))
			start_cmd = start_cmd->next;
		else if (start_cmd->type == WORD)
		{
			split_res = ft_split(start_cmd->str, ' ');
			j = 0;
			while (split_res && split_res[j])
			{
				cmd_args[i++] = rest_sp(split_res[j++]);
			}
			free(split_res);
		}
		if (start_cmd)
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

	if (!list || check_syntax_token(list) != 1)
	{
		shell->exit_status = 2;
		return (NULL);
	}
	current = list;
	while (current)
	{
		start_cmd = current;
		nbr_args = get_nbr_args_one_cmd(start_cmd, 0);
		while (current && current->type != PIPE)
			current = current->next;
		new = create_one_cmd(shell, start_cmd, nbr_args);
		list_add_back_cmd(&shell->cmds, new);
		if (current && current->type == PIPE)
			current = current->next;
	}
	return (shell->cmds);
}
