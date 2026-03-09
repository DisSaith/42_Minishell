/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_empty.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 10:40:48 by acohaut           #+#    #+#             */
/*   Updated: 2026/03/06 11:01:35 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
// Updates the '_' env variable with the last executed command path/arg.
*/
void	ft_update_underscore(t_shell *shell, char *value)
{
	t_env	*node;
	char	*str;

	if (!shell || !value)
		return ;
	node = ft_get_env_node(shell->env, "_");
	if (node)
	{
		free(node->content);
		node->content = ft_strdup(value);
	}
	else
	{
		str = ft_strjoin("_=", value);
		if (!str)
			return ;
		ft_fill_export(&shell->env, str);
		free(str);
	}
}

/*
// Initializes a minimal default env (PWD, SHLVL, _) for the shell.
*/
int	ft_empty_env(t_shell *shell, t_env **env)
{
	char	*temp;
	char	*pwd;
	t_env	*last;

	temp = getcwd(NULL, 0);
	last = NULL;
	if (!temp)
		return (0);
	pwd = ft_strjoin("PWD=", temp);
	if (!pwd)
		return (free(temp), 0);
	if (!ft_append_env_node(env, &last, pwd))
		return (free(temp), free(pwd), 0);
	free(temp);
	free(pwd);
	if (!ft_append_env_node(env, &last, "SHLVL=1"))
		return (free_env(shell, env), 0);
	if (!ft_append_env_node(env, &last, "_=path_cmd"))
		return (free_env(shell, env), 0);
	return (1);
}
