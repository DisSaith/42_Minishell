/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 09:45:33 by nofelten          #+#    #+#             */
/*   Updated: 2026/03/10 10:34:46 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
//Function to check if the flag -n for builtin echo is right of not
*/
int	check_flag_echo(char *flag)
{
	size_t	i;

	if (!flag)
		return (0);
	i = 0;
	if (flag[i] == '-')
		i++;
	else
		return (0);
	while (flag && flag[i] == 'n')
		i++;
	if (flag[i] == '\0')
		return (1);
	else
		return (0);
}

/*
//(part 2) Built-in echo function -> handles flag -n or multi args
*/
int	execute_echo(t_cmd *cmd, int i)
{
	if (check_flag_echo(cmd->cmd_args[i]))
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
