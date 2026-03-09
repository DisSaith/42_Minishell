/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 11:52:02 by nofelten          #+#    #+#             */
/*   Updated: 2026/03/06 14:12:14 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
// Removes and frees an env node matching the given string identifier.
*/
int	ft_unset_var(t_env **env, char *str)
{
	t_env	*current;
	t_env	*tmp;

	tmp = NULL;
	if (!env || !str)
		return (0);
	if (!ft_is_valid_identifier(str))
		return (1);
	current = *env;
	while (current)
	{
		if (!ft_strcmp(current->name, str))
		{
			if (tmp == NULL)
				*env = current->next;
			else
				tmp->next = current->next;
			return (ft_free_node(current), 1);
		}
		tmp = current;
		current = current->next;
	}
	return (1);
}

/*
// Executes unset builtin by removing variables matching the arguments.
*/
int	ft_unset(t_env **env, char **args)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	while (args[i])
	{
		if (!ft_unset_var(env, args[i]))
			exit_status = 1;
		i++;
	}
	return (exit_status);
}

/*
//Functiom who free each node and is content
*/
void	ft_free_node(t_env *node)
{
	if (!node)
		return ;
	free(node->name);
	free(node->content);
	free(node);
}
