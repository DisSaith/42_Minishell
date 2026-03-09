/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:23:39 by acohaut           #+#    #+#             */
/*   Updated: 2026/03/07 17:22:33 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
//Executes one cmd base on his name and his path
*/
void	execute_one_cmd(t_shell *shell, t_cmd *cmd)
{
	char	*cmd_path;

	if (!cmd || !cmd->cmd_args || cmd->cmd_args[0][0] == '\0')
		error_exit_wrong_path(ft_strdup(""), shell, cmd);
	cmd_path = return_path_cmd(shell->envp, cmd->cmd_args[0]);
	if (!cmd_path)
		error_exit_wrong_path(cmd_path, shell, cmd);
	ft_update_underscore(shell, cmd_path);
	execve(cmd_path, cmd->cmd_args, shell->envp);
	error_exit_execve(cmd_path, shell, cmd);
}

/*
//Checks if it's a built-in function then execute it
*/
int	exec_builtin_cmd(t_shell *shell, t_cmd *cmd, int pipe)
{
	if (!cmd || !cmd->cmd_args || cmd->cmd_args[0][0] == '\0')
		shell->exit_status = 1;
	else
	{
		ft_update_underscore(shell, cmd->cmd_args[0]);
		if (ft_strncmp("cd", cmd->cmd_args[0], 3) == 0)
			shell->exit_status = change_directory(cmd, pipe);
		else if (ft_strncmp("env", cmd->cmd_args[0], 4) == 0)
			shell->exit_status = ft_env(shell->env, cmd);
		else if (ft_strncmp("unset", cmd->cmd_args[0], 6) == 0)
			shell->exit_status = ft_unset(&shell->env, cmd->cmd_args);
		else if (ft_strncmp("export", cmd->cmd_args[0], 7) == 0)
			shell->exit_status = ft_export(&shell->env, cmd->cmd_args);
		else if (ft_strncmp("exit", cmd->cmd_args[0], 5) == 0)
			shell->exit_status = ft_exit(shell, cmd, pipe);
		else if (ft_strncmp("echo", cmd->cmd_args[0], 5) == 0)
			shell->exit_status = echo(cmd);
		else if (ft_strncmp("pwd", cmd->cmd_args[0], 4) == 0)
			shell->exit_status = ft_pwd();
	}
	if (pipe)
		return (free_env(shell, &shell->env), free_all(shell),
			shell->exit_status);
	return (shell->exit_status);
}

/*
//Redirects the streams (if necessary) before execute the cmd
*/
int	child_process(t_shell *shell, t_cmd *cmd, int index, int pipe)
{
	set_signal_exec();
	if (!redirection_fd(shell, cmd, index == shell->nbr_cmds - 1))
	{
		free_env(shell, &shell->env);
		free_all(shell);
		shell->exit_status = 1;
		return (0);
	}
	if (is_builtin_cmd(cmd->cmd_args[0]) && pipe == YES)
	{
		shell->exit_status = exec_builtin_cmd(shell, cmd, YES);
		return (0);
	}
	execute_one_cmd(shell, cmd);
	return (1);
}

/*
//Redirect the streams then execute one built_in cmd (if nbr_cmds == 1)
*/
int	builtin_process(t_shell *shell, t_cmd *cmd)
{
	int	savefd[2];

	savefd[0] = dup(STDIN_FILENO);
	savefd[1] = dup(STDOUT_FILENO);
	if (!redirection_fd(shell, cmd, YES))
	{
		close(savefd[0]);
		close(savefd[1]);
		shell->exit_status = 1;
		return (shell->exit_status);
	}
	shell->exit_status = exec_builtin_cmd(shell, cmd, NO);
	dup2(savefd[0], STDIN_FILENO);
	dup2(savefd[1], STDOUT_FILENO);
	close(savefd[0]);
	close(savefd[1]);
	if (shell->envp)
		shell->envp = free_tab_tab(shell->envp);
	shell->envp = ft_env_to_tab(shell->env);
	return (shell->exit_status);
}

/*
//Prepare before execution of one or more cmd
*/
int	process_cmd(t_shell *shell)
{
	if (shell->nbr_cmds == 1 && is_builtin_cmd(shell->cmds->cmd_args[0]))
		return (builtin_process(shell, shell->cmds));
	shell->pid = ft_calloc(shell->nbr_cmds, sizeof(pid_t));
	if (!shell->pid)
		error_exit("malloc", shell);
	if (shell->nbr_cmds > 1)
		return (proc_cmd_multi_pipe1(shell));
	prepare_single_cmd(shell);
	sigint_signal_ignore();
	shell->pid[0] = fork();
	if (shell->pid[0] < 0)
		error_exit("fork", shell);
	if (shell->pid[0] == 0)
	{
		if (!child_process(shell, shell->cmds, 0, NO))
			exit(shell->exit_status);
	}
	waitpid_processes(shell, shell->nbr_cmds);
	set_signal_capture();
	return (shell->exit_status);
}
