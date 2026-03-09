/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 19:17:01 by nofelten          #+#    #+#             */
/*   Updated: 2026/03/02 18:28:02 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
// Adds or updates an env variable, after validating the identifier.
*/
int	ft_fill_export(t_env **env, char *str)
{
	t_env	*current;
	t_env	*new_node;
	int		i;
	char	*name;

	i = 0;
	if (!env || !str)
		return (0);
	while (str[i] != '=' && str[i])
		i++;
	name = ft_strndup(str, i);
	if (!name)
		return (0);
	if (!ft_is_valid_identifier(name))
		return (free(name), error_export(str), 0);
	current = ft_get_env_node(*env, name);
	if (!current)
	{
		new_node = ft_env_lstnew(str);
		if (!new_node)
			return (free(name), 0);
		ft_env_lstadd_back(env, new_node);
		return (free(name), 1);
	}
	return (free(name), ft_update_env_node(current, str));
}

/*
// Executes export: prints sorted env or processes given arguments.
*/
int	ft_export(t_env **env, char **args)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	if (!args[1])
		return (sorted_env(*env), 0);
	while (args[i])
	{
		if (!ft_fill_export(env, args[i]))
			exit_status = 1;
		i++;
	}
	return (exit_status);
}

/*
// Converts the env linked list into a newly allocated string array.
*/
char	**export_to_tab(t_env *env)
{
	char	**tab;
	int		i;

	tab = malloc(sizeof(char *) * (export_size(env) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (env)
	{
		if (!env->content)
		{
			tab[i] = ft_strdup(env->name);
			if (!tab[i])
				return (free_tab_tab(tab), NULL);
		}
		else
		{
			tab[i] = format_export_str(env);
			if (!tab[i])
				return (free_tab_tab(tab), NULL);
		}
		i++;
		env = env->next;
	}
	return (tab[i] = NULL, tab);
}

/*
// Formats an env node into a newly allocated 'NAME="VALUE"' string for output.
*/
char	*format_export_str(t_env *node)
{
	char	*temp;
	char	*str_surrounded;
	char	*str;

	temp = ft_strjoin(node->name, "=");
	if (!temp)
		return (NULL);
	str_surrounded = ft_str_surround(node->content, '"');
	if (!str_surrounded)
		return (free(temp), NULL);
	str = ft_strjoin(temp, str_surrounded);
	free(str_surrounded);
	free(temp);
	if (!str)
		return (NULL);
	return (str);
}

/*
// Updates an existing env node's content using a "NAME=VALUE" string.
*/
int	ft_update_env_node(t_env *env, char *str)
{
	int	i;

	i = 0;
	if (!env || !str)
		return (0);
	while (str[i] != '=' && str[i])
		i++;
	if (str[i] == '=')
	{
		free(env->content);
		env->content = ft_strdup(str + i + 1);
		if (!env->content)
			return (0);
	}
	return (1);
}
