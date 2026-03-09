/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:13:11 by nofelten          #+#    #+#             */
/*   Updated: 2026/03/07 14:35:00 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
//Searchs a var env_node and return his content (or NULL) if he exists
*/
char	*get_env_node_content(t_shell *shell, t_env *env, char *name)
{
	char	*str;

	if (!env || !name)
		return (NULL);
	str = NULL;
	while (env)
	{
		if (ft_strncmp("?", name, 1) == 0)
		{
			str = ft_itoa(shell->exit_status);
			if (ft_strlen(name) > 1)
				str = ft_strjoin_gnl(str, name + 1);
			return (str);
		}
		if (ft_strcmp(env->name, name) == 0)
			return (ft_strdup(env->content));
		env = env->next;
	}
	return (NULL);
}

/*
//Returns the content of the env variable if she exists
*/
char	*check_if_is_var_env(t_shell *shell, char *str, size_t *i)
{
	char	*env_content;
	char	*var;
	size_t	start;

	start = *i;
	while (str[*i] && is_var_char(str[*i]))
		(*i)++;
	if (start == *i)
		return (ft_strdup("$"));
	var = ft_strndup(&str[start], *i - start);
	if (!var)
		return (NULL);
	env_content = get_env_node_content(shell, shell->env, var);
	free(var);
	if (!env_content)
		return (ft_strdup(""));
	return (env_content);
}

/*
//(part 2) If $ exists, expand or not the content of the token with the
//content of the env variable (if she exists)
*/
char	*expander2(t_shell *shell, char *str, char *cmd_arg, char *tmp)
{
	t_expander	x;

	init_struct_expander(&x);
	while (str && str[x.i])
	{
		if ((str[x.i] == '\'' || str[x.i] == '\"') && !x.quote)
			x.quote = str[x.i];
		else if (x.quote && str[x.i] == x.quote)
			x.quote = 0;
		if (str[x.i] == '$' && x.quote != '\'')
		{
			tmp = ft_strndup(&str[x.start], x.i - x.start);
			cmd_arg = ft_strjoin_expander(cmd_arg, tmp);
			x.i++;
			tmp = check_if_is_var_env(shell, str, &x.i);
			cmd_arg = ft_strjoin_expander(cmd_arg, tmp);
			x.start = x.i;
		}
		else
			x.i++;
	}
	tmp = ft_strndup(&str[x.start], x.i - x.start);
	cmd_arg = ft_strjoin_gnl(cmd_arg, tmp);
	return (free(tmp), cmd_arg);
}

/*
//(part 1) check the token state and return the extended string or not
//depending ont the token state wheter of not a $ is present 
*/
char	*expander(t_shell *shell, char *str)
{
	char	*cmd_arg;
	char	*tmp;

	if (!str)
		return (NULL);
	cmd_arg = NULL;
	tmp = NULL;
	cmd_arg = expander2(shell, str, cmd_arg, tmp);
	return (cmd_arg);
}
