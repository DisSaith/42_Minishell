/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:05:03 by acohaut           #+#    #+#             */
/*   Updated: 2025/11/20 13:04:01 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	s_len;
	size_t	i;
	size_t	debut;

	if (!s)
		return (NULL);
	debut = (size_t)start;
	s_len = ft_strlen(s);
	if (debut >= s_len)
		return (ft_strdup(""));
	if (len > s_len - debut)
		len = s_len - debut;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len && s[debut])
	{
		result[i] = s[debut];
		debut++;
		i++;
	}
	result[i] = '\0';
	return (result);
}
