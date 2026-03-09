/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:38:07 by nofelten          #+#    #+#             */
/*   Updated: 2026/02/19 21:39:06 by nofelten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
// Allocates a new string by enclosing the input with a given char.
*/
char	*ft_str_surround(char *str, char c)
{
	char	*str_surrounded;
	int		len;
	int		i;

	if (!str)
		return (NULL);
	i = 1;
	len = ft_strlen(str);
	str_surrounded = malloc(sizeof(char) * (len + 3));
	if (!str_surrounded)
		return (NULL);
	str_surrounded[0] = c;
	while (len >= i)
	{
		str_surrounded[i] = str[i - 1];
		i++;
	}
	str_surrounded[i] = c;
	str_surrounded[i + 1] = '\0';
	return (str_surrounded);
}

/*
//Returns the size of the env struct
*/
int	export_size(t_env *env)
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
//Print like the built-in function export
*/
void	print_export(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("declare -x %s\n", tab[i]);
		i++;
	}
	free_tab_tab(tab);
}

/*
//Sort env struct based on ASCII order
*/
void	sorted_env(t_env *env)
{
	char	**tab;
	char	*temp;
	int		i;
	int		j;

	i = 0;
	tab = export_to_tab(env);
	if (!tab)
		return ;
	while (tab[i])
	{
		j = i + 1;
		while (tab[j])
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				temp = tab[i];
				tab[i] = tab[j];
				tab[j] = temp;
			}
			j++;
		}
		i++;
	}
	print_export(tab);
}

/*
//Searchs and return a node (or NULL) by using char *name as parameter 
*/
t_env	*ft_get_env_node(t_env *env, char *name)
{
	if (!env || !name)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			return (env);
		env = env->next;
	}
	return (NULL);
}
