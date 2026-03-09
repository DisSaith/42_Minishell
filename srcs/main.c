/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:23:39 by acohaut           #+#    #+#             */
/*   Updated: 2026/03/09 15:03:22 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
//Initialises Shell struct where all data is stored
*/
void	prepare_shell(t_shell *shell, char *envp[])
{
	if (shell->started == 0)
	{
		ft_init_env(shell, envp, &shell->env);
		shell->envp = ft_env_to_tab(shell->env);
		shell->started = 1;
	}
	shell->delimiter = NULL;
	shell->prompt = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
	shell->current = NULL;
	shell->nbr_cmds = 0;
	shell->heredoc = NULL;
	shell->nbr_heredocs = 1;
	shell->pid = NULL;
	shell->pipefd[0] = -2;
	shell->pipefd[1] = -2;
	shell->savefd[0] = -2;
	shell->savefd[1] = -2;
	shell->heredocfd = -2;
	shell->fd_read = STDIN_FILENO;
}

/*
//Enables minishell to function correctly before the while (1) loop
*/
void	init_before_start(t_shell *shell, char **av)
{
	(void)av;
	rl_catch_signals = 0;
	shell->exit_status = 0;
	shell->started = 0;
	shell->envp = NULL;
}

/*
//Main fonction of minishell
*/
int	main(int ac, char **av, char *envp[])
{
	int		result_get_inputs;
	t_shell	shell;

	if (ac != 1)
		return (write(2, "Usage: ./minishell\n", 19), 1);
	init_before_start(&shell, av);
	get_shell_ptr(&shell);
	while (1)
	{
		set_signal_capture();
		prepare_shell(&shell, envp);
		result_get_inputs = get_inputs(&shell);
		if (result_get_inputs == CTRL_D)
			return (free_env(&shell, &shell.env), write(1, "exit\n", 5), 0);
		else if (result_get_inputs == 0)
			continue ;
		shell.exit_status = process_cmd(&shell);
		close_all(&shell);
		free_all(&shell);
	}
	rl_clear_history();
	return (close_all(&shell), free_all(&shell),
		free_env(&shell, &shell.env), shell.exit_status);
}
