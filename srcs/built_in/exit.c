/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 09:45:33 by nofelten          #+#    #+#             */
/*   Updated: 2026/03/09 14:16:10 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
//Function ft_atoll modified to check for overflows and limits
*/
long long	check_long_long_limits(char *arg)
{
	long long	i;
	long long	sign;
	long long	prev;
	long long	value;

	i = 0;
	sign = 1;
	value = 0;
	while (arg[i] && ft_isspace(arg[i]))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
	{
		if (arg[i] == '-')
			sign = -1;
		i++;
	}
	while (arg[i] && ft_isdigit(arg[i]))
	{
		prev = value;
		value = (value * 10) + (arg[i] - '0');
		if (prev > value)
			return (-1);
		i++;
	}
	return (sign * value);
}

/*
//Function that checks char *exit_status and returns is as un int
*/
int	get_exit_status(char *arg, int argc, t_shell *shell)
{
	long long	exit_status;

	if (!arg || argc == 1)
		return (shell->exit_status);
	if (ft_strncmp(arg, "-9223372036854775808", 21) == 0
		|| ft_strncmp(arg, "0", 2) == 0)
	{
		shell->exit_status = 0;
		return (0);
	}
	exit_status = check_long_long_limits(arg);
	if (exit_status == -1 || exit_status == 0)
		return (-1);
	if (exit_status > 255 || exit_status < 0)
		exit_status = exit_status % 256;
	shell->exit_status = exit_status;
	return (shell->exit_status);
}

/*
//Displays the error message if the the number is invalid + free
*/
void	perror_ft_exit(t_shell *shell, t_cmd *cmd, int pipe)
{
	if (!cmd || !cmd->cmd_args)
		return ;
	if (!pipe)
		write(1, "exit\n", 5);
	write(2, "minishell: exit: ", 17);
	write(2, cmd->cmd_args[1], ft_strlen(cmd->cmd_args[1]));
	write(2, ": numeric argument required\n", 28);
	if (pipe)
		return ;
	shell->exit_status = 2;
	close_all(shell);
	free_env(shell, &shell->env);
	free_all(shell);
	exit(shell->exit_status);
}

/*
//Exit the current process and return an exit_status
*/
size_t	ft_exit(t_shell *shell, t_cmd *cmd, int pipe)
{
	int		argc;

	if (!cmd || !cmd->cmd_args)
		return (1);
	argc = get_nbr_args_cmd(cmd);
	if (get_exit_status(cmd->cmd_args[1], argc, shell) == -1)
	{
		perror_ft_exit(shell, cmd, pipe);
		if (pipe)
			return (2);
	}
	if (argc > 2 && !pipe)
		return (write(2, "exit\nminishell: exit: too many arguments\n", 41), 1);
	else if (argc > 2 && pipe)
		return (write(2, "minishell: exit: too many arguments\n", 36), 1);
	if (pipe)
		return (shell->exit_status);
	close_all(shell);
	free_env(shell, &shell->env);
	free_all(shell);
	write(1, "exit\n", 5);
	exit(shell->exit_status);
	return (shell->exit_status);
}
