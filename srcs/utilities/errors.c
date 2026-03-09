/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:23:44 by acohaut           #+#    #+#             */
/*   Updated: 2026/03/09 11:52:31 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
//Displays the error message, closes the fd (if they exist) and exit (1)
*/
void	error_exit(char *error, t_shell *shell)
{
	close_all(shell);
	free_env(shell, &shell->env);
	free_all(shell);
	perror(error);
	exit(1);
}

/*
//Displays the error for a built-in cmd based on its args (if any)
*/
void	error_builtin(char *cmd, char *arg)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	if (arg)
	{	
		if (access(arg, F_OK) != 0)
		{
			write(2, arg, ft_strlen(arg));
			write(2, ": No such file or directory\n", 28);
		}
		else
			perror(arg);
	}
	else
		write(2, "too many arguments\n", 19);
}

/*
//Displays an error message for export
*/
void	error_export(char *args)
{
	write(2, "minishell: export: `", 20);
	write(2, args, ft_strlen(args));
	write(2, "': not a valid identifier\n", 26);
}
