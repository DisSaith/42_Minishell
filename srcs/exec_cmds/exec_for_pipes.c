/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_for_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:23:39 by acohaut           #+#    #+#             */
/*   Updated: 2026/03/07 17:21:41 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
//(part 2) Prepare to execute multiple cmds for one of more pipes
*/
void	proc_cmd_multi_pipe2(int i, t_shell *shell, t_cmd *cmd)
{
	if (i < shell->nbr_cmds - 1)
		if (pipe(shell->pipefd) == -1)
			error_exit("pipe", shell);
	sigint_signal_ignore();
	shell->pid[i] = fork();
	if (shell->pid[i] < 0)
		error_exit("fork", shell);
	else if (shell->pid[i] == 0)
	{
		if (!child_process(shell, cmd, i, YES))
			exit(shell->exit_status);
	}
	if (i != 0)
		close(shell->fd_read);
	if (i < shell->nbr_cmds - 1)
	{
		close(shell->pipefd[1]);
		shell->fd_read = shell->pipefd[0];
	}
}

/*
//(part 1) Process every cmd for pipes then wait every childs process
*/
int	proc_cmd_multi_pipe1(t_shell *shell)
{
	int		i;
	t_cmd	*current;

	i = 0;
	current = shell->cmds;
	while (i < shell->nbr_cmds && current)
	{
		proc_cmd_multi_pipe2(i, shell, current);
		current = current->next;
		i++;
	}
	waitpid_processes(shell, shell->nbr_cmds);
	set_signal_capture();
	return (shell->exit_status);
}

/*
//Wait every child process and return the last exit_status
*/
void	waitpid_processes(t_shell *shell, int nbr_cmds)
{
	int	i;
	int	status;
	int	printed;

	status = 0;
	i = 0;
	printed = 0;
	while (i < nbr_cmds)
	{
		waitpid(shell->pid[i], &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT && !printed)
				write(1, "\n", 1);
			else if (WTERMSIG(status) == SIGQUIT && !printed)
				write(1, "Quit (core dumped)\n", 19);
			printed = 1;
			status = 128 + WTERMSIG(status);
		}
		if (i == nbr_cmds - 1)
			shell->exit_status = status;
		i++;
	}
}
