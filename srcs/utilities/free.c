/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:11:30 by acohaut           #+#    #+#             */
/*   Updated: 2026/03/07 16:00:07 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
//Free an tab_tab of char *
*/
void	*free_tab_tab(char **tab)
{
	size_t	i;

	if (!tab)
		return (NULL);
	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

/*
//Free a str and return NULL
*/
void	*free_str(char *str)
{
	free(str);
	return (NULL);
}

/*
//Free everything that was used to launch cmds based on 1 input
*/
void	free_all(t_shell *shell)
{
	if (shell->pid)
		free(shell->pid);
	if (shell->cmds)
		free_list_cmd(&shell->cmds);
	if (shell->tokens)
		free_list_token(&shell->tokens);
	if (access(".heredoc_tmp", F_OK) == 0)
		unlink(".heredoc_tmp");
}

/*
//Free everything necessary for the command change_directory
*/
void	free_for_cd(char *pwd, char *path, char *tmp)
{
	free(pwd);
	free(path);
	free(tmp);
}

/*
//Free everything necessary for heredoc to cleanup child process before exit
*/
void	free_heredoc(t_shell *shell, char *expanded, char *rl)
{
	if (rl)
		free(rl);
	if (expanded)
		free(expanded);
	if (shell->delimiter)
		free(shell->delimiter);
	if (shell->prompt)
		free(shell->prompt);
	if (shell->current)
		free(shell->current);
	if (shell->pid)
		free(shell->pid);
	if (shell->tokens)
		free_list_token(&shell->tokens);
	if (shell->cmds)
		free_list_cmd(&shell->cmds);
	free_env(shell, &shell->env);
}
