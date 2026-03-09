/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 13:57:17 by nofelten          #+#    #+#             */
/*   Updated: 2026/03/09 12:13:28 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
//Captures signals and blocks the SIGQUIT signal (CTRL+\) and calls the fonction
//that modifies the behaviour of the SIGINT signal (CTRL+C)
*/
int	set_signal_capture(void)
{
	struct sigaction	act;

	sigint_signal_action();
	sigemptyset(&act.sa_mask);
	act.sa_handler = SIG_IGN;
	act.sa_flags = 0;
	sigaction(SIGQUIT, &act, NULL);
	return (0);
}

/*
//Modifies the behaviour of the SIGINT signal (CRTL+C) by creating a new prompt
*/
void	sigint_handler(int signal)
{
	t_shell	*shell;

	shell = get_shell_ptr(NULL);
	(void)signal;
	write(1, "^C", 2);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	shell->exit_status = 130;
}

/*
//Ignore SIGINNT signals (CTRL+C)
*/
void	sigint_signal_ignore(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_handler = SIG_IGN;
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);
}

/*
//Etablishment of the SIGINT signal (CTRL+C) with its modified action
*/
void	sigint_signal_action(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_handler = &sigint_handler;
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);
}

/*
//Reset the signals to default behavior for exec cmds
*/
void	set_signal_exec(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_handler = SIG_DFL;
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
