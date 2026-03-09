/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 09:45:33 by nofelten          #+#    #+#             */
/*   Updated: 2026/03/03 14:30:54 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
//(part 2) Built-in echo function -> handles flag -n or multi args
*/
int	execute_echo(t_cmd *cmd, int i)
{
	if (ft_strncmp("-n", cmd->cmd_args[i], 3) == 0)
	{
		while (cmd->cmd_args[i])
		{
			i++;
			write(1, cmd->cmd_args[i], ft_strlen(cmd->cmd_args[i]));
			if (i < get_nbr_args_cmd(cmd) - 1)
				write(1, " ", 1);
		}
	}
	else
	{
		while (cmd->cmd_args[i])
		{
			write(1, cmd->cmd_args[i], ft_strlen(cmd->cmd_args[i]));
			if (i < get_nbr_args_cmd(cmd) - 1)
				write(1, " ", 1);
			i++;
		}
		return (write(1, "\n", 1), 0);
	}
	return (0);
}

/*
//(part 1) Built-in echo function -> displays its arguments
*/
int	echo(t_cmd *cmd)
{
	int	i;

	if (!cmd || !cmd->cmd_args || !cmd->out
		|| cmd->out == -1 || cmd->in == -1)
		return (1);
	if (get_nbr_args_cmd(cmd) == 1)
		return (write(1, "\n", 1), 0);
	i = 1;
	return (execute_echo(cmd, i));
}
