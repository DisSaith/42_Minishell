/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:03:45 by acohaut           #+#    #+#             */
/*   Updated: 2026/01/29 13:39:45 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
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
		return (NULL);
	while (s1 && s1[i])
		result[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
		result[j++] = s2[i++];
	result[j] = '\0';
	return (result);
}
