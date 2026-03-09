/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 13:57:17 by nofelten          #+#    #+#             */
/*   Updated: 2026/03/09 15:19:55 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
//For heredoc, when SIGINT (CTRL-C) : free and exit(130) the child process
*/
void	sigint_handler_heredoc(int signal)
{
	t_shell	*shell;

	(void)signal;
	shell = get_shell_ptr(NULL);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (shell)
	{
		if (shell->heredocfd > 2)
			close(shell->heredocfd);
		if (shell->delimiter)
			free(shell->delimiter);
		if (shell->prompt)
			free(shell->prompt);
		if (shell->current)
			free(shell->current);
		if (shell->heredoc)
			free(shell->heredoc);
		free_env(shell, &shell->env);
		free_all(shell);
	}
	exit(130);
}

/*
//Modifies the behavior of SIGINT for heredoc
*/
void	set_signal_heredoc(void)
{
	struct sigaction	act;

	rl_catch_signals = 1;
	sigemptyset(&act.sa_mask);
	act.sa_handler = sigint_handler_heredoc;
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);
}
