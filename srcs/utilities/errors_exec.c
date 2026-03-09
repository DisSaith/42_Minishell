/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:23:44 by acohaut           #+#    #+#             */
/*   Updated: 2026/03/09 13:41:43 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
//Displays an error if the command path is incorrect and free + exit (127)
*/
void	error_exit_wrong_path(char *cmd_path, t_shell *shell, t_cmd *cmd)
{
	write(2, "minishell: ", 11);
	write(2, cmd->cmd_args[0], ft_strlen(cmd->cmd_args[0]));
	write(2, ": command not found\n", 20);
	free(cmd_path);
	close_all(shell);
	free_env(shell, &shell->env);
	free_all(shell);
	exit(127);
}

/*
//(part 2) Displays the correct error message if the command execution failed
*/
void	error_exit_execve_path(char *cmd_path, t_shell *shell, t_cmd *cmd)
{
	DIR	*dir;

	if (access(cmd_path, F_OK) != 0)
	{
		write(2, ": No such file or directory\n", 28);
		free(cmd_path);
		free_env(shell, &shell->env);
		free_all(shell);
		exit(127);
	}
	dir = opendir(cmd->cmd_args[0]);
	if (dir)
	{
		write(2, ": Is a directory\n", 17);
		closedir(dir);
		free(cmd_path);
		free_env(shell, &shell->env);
		free_all(shell);
		exit(126);
	}
	write(2, ": Permission denied\n", 20);
	free(cmd_path);
	free_env(shell, &shell->env);
	free_all(shell);
	exit(126);
}

/*
//(part 1) Displays the correct error message if the command execution failed
*/
void	error_exit_execve(char *cmd_path, t_shell *shell, t_cmd *cmd)
{
	close_all(shell);
	write(2, "minishell: ", 11);
	write(2, cmd->cmd_args[0], ft_strlen(cmd->cmd_args[0]));
	if (ft_strchr(cmd_path, '/'))
		error_exit_execve_path(cmd_path, shell, cmd);
	else
	{
		write(2, ": command not found\n", 20);
		free(cmd_path);
		free_env(shell, &shell->env);
		free_all(shell);
		exit(127);
	}
}
