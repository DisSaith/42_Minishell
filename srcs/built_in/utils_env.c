/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:10:42 by nofelten          #+#    #+#             */
/*   Updated: 2026/03/06 10:43:42 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
//Returns the size of env structure
*/
int	ft_env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

/*
// Appends a new env node to the end of the list and updates the tail.
*/
int	ft_append_env_node(t_env **env, t_env **last, char *str)
{
	t_env	*new_node;

	new_node = ft_env_lstnew(str);
	if (!new_node)
		return (0);
	if (!*env)
		*env = new_node;
	else
		(*last)->next = new_node;
	*last = new_node;
	return (1);
}

/*
//Free the struct env and all is nodes
*/
void	free_env(t_shell *shell, t_env **env)
{
	t_env	*current;
	t_env	*next_node;

	if (!env || !*env)
		return ;
	current = *env;
	while (current)
	{
		next_node = current->next;
		free(current->name);
		free(current->content);
		free(current);
		current = next_node;
	}
	*env = NULL;
	if (shell->envp)
		shell->envp = free_tab_tab(shell->envp);
}

/*
// Checks if a string is a valid env variable name (alphanumeric & _).
*/
int	ft_is_valid_identifier(char *name)
{
	int	i;

	i = 0;
	if (!name || !name[i])
		return (0);
	if (!ft_isalpha(name[i]) && name[i] != '_')
		return (0);
	i++;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
