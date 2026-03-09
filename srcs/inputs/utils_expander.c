/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:46:54 by acohaut           #+#    #+#             */
/*   Updated: 2026/03/04 15:43:38 by acohaut          ###   ########.fr       */
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
