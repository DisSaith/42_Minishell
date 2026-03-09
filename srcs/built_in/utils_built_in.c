/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 09:45:33 by nofelten          #+#    #+#             */
/*   Updated: 2026/02/18 15:52:05 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
//Check whether it's a built in cmd of not
*/
int	is_builtin_cmd(char *str)
{
	char	*built_in[8];
	int		i;

	built_in[0] = "exit";
	built_in[1] = "echo";
	built_in[2] = "cd";
	built_in[3] = "pwd";
	built_in[4] = "export";
	built_in[5] = "unset";
	built_in[6] = "env";
	built_in[7] = NULL;
	i = 0;
	while (built_in[i] != NULL)
	{
		if (ft_strncmp(built_in[i], str, ft_strlen(built_in[i]) + 1) == 0)
			return (1);
		i++;
	}
	return (0);
}

/*
//Returns 0 if the argument is NULL or equal to a PIPE (|)
*/
int	is_good_arg(char *arg)
{
	if (!arg)
		return (0);
	if (ft_strncmp("|", arg, 2) == 0)
		return (0);
	return (1);
}

/*
//Calculates and returns the number of arguments in a command
*/
int	get_nbr_args_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return (0);
	i = 0;
	while (cmd->cmd_args[i] != NULL)
		i++;
	return (i);
}
