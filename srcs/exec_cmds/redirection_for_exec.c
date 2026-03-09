/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_for_exec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:23:39 by acohaut           #+#    #+#             */
/*   Updated: 2026/03/03 13:45:52 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
//Redirect if cmd->in > 2 (see fonction int redirection_fd)
//Redirects the streams from infile (popened during parsing)
*/
void	redirection_infile(t_shell *shell, t_cmd *cmd)
{
	if (dup2(cmd->in, STDIN_FILENO) == -1)
		error_exit("dup2", shell);
	close(cmd->in);
	if (shell->fd_read != STDIN_FILENO)
		close(shell->fd_read);
}

/*
//Redirect if cmd->out > 2 (see fonction int redirection_fd)
//Redirects the streams from outfile (popened during parsing)
*/
void	redirection_outfile(t_shell *shell, t_cmd *cmd, int is_last)
{
	if (dup2(cmd->out, STDOUT_FILENO) == -1)
		error_exit("dup2", shell);
	close(cmd->out);
	if (!is_last)
	{
		close(shell->pipefd[0]);
		close(shell->pipefd[1]);
	}
}

/*
//Fonction that redirects streams (if necessary)
*/
int	redirection_fd(t_shell *shell, t_cmd *cmd, int is_last)
{
	if (cmd->in == -1 || cmd->out == -1)
		return (0);
	if (cmd->in > 2)
		redirection_infile(shell, cmd);
	else if (shell->fd_read != STDIN_FILENO)
	{
		if (dup2(shell->fd_read, STDIN_FILENO) == -1)
			error_exit("dup2", shell);
		close(shell->fd_read);
	}
	if (cmd->out > 2)
		redirection_outfile(shell, cmd, is_last);
	else if (!is_last && cmd->out == -2)
	{
		close(shell->pipefd[0]);
		if (dup2(shell->pipefd[1], STDOUT_FILENO) == -1)
			error_exit("dup2", shell);
		close(shell->pipefd[1]);
	}
	return (1);
}
