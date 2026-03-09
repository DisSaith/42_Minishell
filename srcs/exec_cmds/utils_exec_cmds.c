/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 17:33:41 by acohaut           #+#    #+#             */
/*   Updated: 2026/03/06 10:10:22 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
//Searches for $PATH and return if it he's found
*/
char	*find_path(char *envp[])
{
	size_t	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_strchr(envp[i], '/'));
		i++;
	}
	return (NULL);
}

/*
//Searches for and returns the path of the desired command
*/
char	*return_path_cmd(char *envp[], char *cmd)
{
	char	*tmp;
	char	*path;
	char	**paths;
	char	*path_cmd;
	size_t	i;

	if (cmd[0] == '\0')
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
		return (ft_strdup(cmd));
	path = find_path(envp);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path_cmd = ft_strjoin_gnl(tmp, cmd);
		if (access(path_cmd, X_OK) == 0)
			return (free_tab_tab(paths), path_cmd);
		free(path_cmd);
		i++;
	}
	return (free_tab_tab(paths), NULL);
}

/*
//Updates '_' and envp before forking for a single external cmd
*/
void	prepare_single_cmd(t_shell *shell)
{
	char	*path;

	if (is_builtin_cmd(shell->cmds->cmd_args[0]))
		return ;
	path = return_path_cmd(shell->envp, shell->cmds->cmd_args[0]);
	if (path)
		ft_update_underscore(shell, path);
	else
		ft_update_underscore(shell, shell->cmds->cmd_args[0]);
	free(path);
	if (shell->envp)
		shell->envp = free_tab_tab(shell->envp);
	shell->envp = ft_env_to_tab(shell->env);
}
