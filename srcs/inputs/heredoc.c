/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:13:11 by nofelten          #+#    #+#             */
/*   Updated: 2026/03/09 10:55:01 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
//warning message if CTRL-D is inputed
*/
void	warning_message_heredoc(t_shell *shell, char *rl,
			int fd, char *expanded)
{
	write(2, "minishell: warning: here-document delimited by end-of-file", 58);
	write(2, " (wanted `", 10);
	write(2, shell->delimiter, ft_strlen(shell->delimiter));
	write(2, "')\n", 3);
	close(fd);
	free_heredoc(shell, expanded, rl);
	exit(0);
}

/*
//Get and stock user's inputs if the delimiter is inclosed by quotes
*/
void	heredoc_quoted(t_shell *shell, char *delimiter, int fd, int token_state)
{
	char	*rl;
	char	*tmp;
	char	*expanded;

	expanded = NULL;
	tmp = NULL;
	while (1)
	{
		rl = readline("> ");
		if (!rl)
			warning_message_heredoc(shell, rl, fd, expanded);
		expanded = expander2(shell, rl, expanded, tmp);
		if ((ft_strcmp(delimiter, expanded) == 0 && token_state == IN_DQUOTE)
			|| (ft_strcmp(delimiter, rl) == 0 && token_state == IN_SQUOTE))
			break ;
		write(fd, rl, ft_strlen(rl));
		write(fd, "\n", 1);
		expanded = free_str(expanded);
		rl = free_str(rl);
	}
	close(fd);
	free_heredoc(shell, expanded, rl);
	exit(0);
}

/*
//Stock user's inputs and expande if necessary (if var env exists)
*/
void	heredoc_not_quoted(t_shell *shell, char *delimiter, int fd)
{
	char	*rl;
	char	*tmp;
	char	*expanded;

	expanded = NULL;
	tmp = NULL;
	while (1)
	{
		rl = readline("> ");
		if (!rl)
			warning_message_heredoc(shell, rl, fd, expanded);
		expanded = expander2(shell, rl, expanded, tmp);
		if (ft_strcmp(delimiter, expanded) == 0)
			break ;
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		rl = free_str(rl);
		expanded = free_str(expanded);
	}
	close(fd);
	free_heredoc(shell, expanded, rl);
	exit(0);
}

/*
//Return the good file descriptor if success or if a signal was received
*/
int	return_fd_heredoc(t_shell *shell)
{
	if (shell->exit_status == 0)
		return (open(shell->heredoc, O_RDONLY));
	else
		return (-1);
}

/*
//Check the DELIMITER state (if quoted or not) then stock user's inputs
*/
int	handle_heredoc(t_shell *shell, t_token *current, int fd)
{
	shell->pid = ft_calloc(1, sizeof(pid_t));
	if (!shell->pid)
		error_exit("malloc", shell);
	shell->delimiter = ft_strdup(current->str);
	shell->pid[0] = fork();
	if (shell->pid[0] < 0)
		error_exit("fork", shell);
	sigint_signal_ignore();
	if (shell->pid[0] == 0)
	{
		set_signal_heredoc();
		if (current->state == IN_SQUOTE || current->state == IN_DQUOTE)
			heredoc_quoted(shell, shell->delimiter, fd, current->state);
		else
			heredoc_not_quoted(shell, shell->delimiter, fd);
	}
	waitpid_processes(shell, 1);
	set_signal_capture();
	free(shell->pid);
	shell->pid = NULL;
	shell->delimiter = free_str(shell->delimiter);
	close(fd);
	fd = return_fd_heredoc(shell);
	return (fd);
}
