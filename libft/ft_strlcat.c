/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:26:08 by acohaut           #+#    #+#             */
/*   Updated: 2025/11/20 13:02:10 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_d;
	size_t	len_d_start;
	size_t	len_s_start;

	len_d_start = ft_strlen((const char *)dest);
	len_s_start = ft_strlen(src);
	i = 0;
	len_d = ft_strlen((const char *)dest);
	if (dstsize == 0)
		return (len_s_start);
	if (dstsize < len_d)
		return (len_s_start + dstsize);
	while (src[i] && (dstsize - 1) > len_d)
	{
		dest[len_d] = src[i];
		i++;
		len_d++;
	}
	dest[len_d] = '\0';
	return (len_d_start + len_s_start);
}
