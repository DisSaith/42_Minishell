/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 09:45:33 by nofelten          #+#    #+#             */
/*   Updated: 2026/03/06 15:17:21 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
//Move to a folder based on the relative of absolute path
*/
int	change_directory(t_cmd *cmd, int pipe)
{
	char	**tab;
	char	*pwd;
	char	*path;
	char	*tmp;
	int		nbr_args;

	nbr_args = get_nbr_args_cmd(cmd);
	if (nbr_args > 2)
		return (error_builtin(cmd->cmd_args[0], NULL), 1);
	tab = cmd->cmd_args;
	if (pipe && is_good_arg(tab[1]) && access(tab[1], F_OK) != 0)
		return (error_builtin(tab[0], tab[1]), 1);
	else if (pipe)
		return (0);
	if (nbr_args == 1 || (nbr_args == 2 && !ft_strcmp("~", tab[1])))
		return (chdir(getenv("HOME")), 0);
	pwd = getcwd(NULL, 0);
	tmp = ft_strjoin(pwd, "/" );
	path = ft_strjoin(tmp, tab[1]);
	if (access(path, R_OK) == 0)
		return (chdir(path), free_for_cd(pwd, path, tmp), 0);
	else if (access(tab[1], R_OK) == 0)
		return (chdir(tab[1]), free_for_cd(pwd, path, tmp), 0);
	return (error_builtin(tab[0], tab[1]), free_for_cd(pwd, path, tmp), 1);
}
