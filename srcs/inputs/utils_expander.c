/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:46:54 by acohaut           #+#    #+#             */
/*   Updated: 2026/03/10 15:52:40 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
//Ft_strjoin for the expander (free s1 and s2)
*/
char	*ft_strjoin_expander(char *s1, char *s2)
{
	char	*result;
	size_t	i;
	size_t	j;
	size_t	size;

	if (!s1 && !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (size + 1));
	if (!result)
		return (free(s1), free(s2), NULL);
	while (s1 && s1[i])
		result[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
		result[j++] = s2[i++];
	result[j] = '\0';
	if (s1)
		free(s1);
	return (free(s2), result);
}

/*
//Function for expander when an $ is not unclosed by quotes
*/
char	*ft_strdup_nospaces(char *str)
{
	size_t	i;
	size_t	len;
	char	*content;
	char	*tmp;

	i = 0;
	content = NULL;
	tmp = NULL;
	while (str && str[i])
	{
		len = 0;
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (!str || !str[i] || str[i] == '\0')
			break ;
		while (str[i + len] && !ft_isspace(str[i + len]))
			len++;
		tmp = ft_strndup(&str[i], len);
		content = ft_strjoin_gnl(content, tmp);
		content = ft_strjoin_gnl(content, " ");
		tmp = free_str(tmp);
		i += len;
	}
	tmp = ft_strtrim(content, " ");
	return (free(content), tmp);
}

/*
//Protect spaces for expander
*/
char	*protect_spaces(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == ' ')
			str[i] = '\1';
		i++;
	}
	return (str);
}

/*
//Initialisation of the struct use in the function expander2
*/
void	init_struct_expander(t_expander *x)
{
	x->i = 0;
	x->start = 0;
	x->quote = 0;
}

/*
//Check if we are in the name of un environment variable ($NAME)
*/
int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}
