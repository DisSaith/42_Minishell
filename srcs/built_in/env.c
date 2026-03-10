/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 09:30:04 by nofelten          #+#    #+#             */
/*   Updated: 2026/03/10 14:12:48 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
// Allocates a new environment list node by splitting a "NAME=VALUE" string.
*/
t_env	*ft_env_lstnew(char *str)
{
	size_t	i;
	t_env	*new_node;

	i = 0;
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	new_node->name = ft_strndup(str, i);
	if (!new_node->name)
		return (free(new_node), NULL);
	if (str[i] == '=')
	{
		i++;
		new_node->content = ft_strdup(str + i);
		if (!new_node->content)
			return (free(new_node->name), free(new_node), NULL);
	}
	else
		new_node->content = NULL;
	new_node->next = NULL;
	return (new_node);
}

/*
//Initialises env structure based on char **envp (empty or not)
*/
int	ft_init_env(t_shell *shell, char **envp, t_env **env)
{
	int		i;
	t_env	*new_node;
	t_env	*last;

	i = 0;
	last = NULL;
	if (env)
		*env = NULL;
	if (!envp || !*envp)
		return (ft_empty_env(shell, env));
	while (envp[i])
	{
		new_node = ft_env_lstnew(envp[i]);
		if (!new_node)
			return (free_env(shell, env), 0);
		if (!*env)
			*env = new_node;
		else
			last->next = new_node;
		last = new_node;
		i++;
	}
	return (1);
}

/*
//Displays all environment arguments
*/
int	ft_env(t_env *env, t_cmd *cmd)
{
	t_env	*current;
	t_shell	*shell;

	shell = get_shell_ptr(NULL);
	if (!env || !cmd || !cmd->cmd_args)
		return (1);
	if (get_nbr_args_cmd(cmd) > 1)
	{
		if (ft_strcmp("-i", cmd->cmd_args[1]) == 0)
			return (0);
		return (error_builtin(cmd->cmd_args[0], cmd->cmd_args[1]), 127);
	}
	current = env;
	while (current)
	{
		if (!current->content)
		{
			current = current->next;
			continue ;
		}
		printf("%s=", current->name);
		printf("%s\n", current->content);
		current = current->next;
	}
	return (0);
}

/*
//Creates shell->envp char ** (tab_tab) based on env structure
*/
char	**ft_env_to_tab(t_env *env)
{
	t_env	*current;
	char	**tab;
	char	*temp;
	int		i;

	tab = malloc(sizeof(char *) * (ft_env_size(env) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	current = env;
	while (current)
	{
		if (current->content)
		{
			temp = ft_strjoin(current->name, "=");
			if (!temp)
				return (free_tab_tab(tab), NULL);
			tab[i] = ft_strjoin_gnl(temp, current->content);
			if (!tab[i])
				return (free_tab_tab(tab), NULL);
			i++;
		}
		current = current->next;
	}
	return (tab[i] = NULL, tab);
}

/*
//Add the new node at the and of the current env structure
*/
void	ft_env_lstadd_back(t_env **env, t_env *new_node)
{
	t_env	*current;

	if (!env || !new_node)
		return ;
	if (!*env)
	{
		*env = new_node;
		return ;
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = new_node;
}
