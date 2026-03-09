/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 19:19:37 by acohaut           #+#    #+#             */
/*   Updated: 2026/01/26 10:27:04 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*memory;
	size_t	i;

	if (size && count > SIZE_MAX / size)
		return (NULL);
	i = 0;
	memory = malloc(size * count);
	if (!memory)
		return (NULL);
	while (i < (count * size))
	{
		((unsigned char *)memory)[i] = (unsigned char)0;
		i++;
	}
	return (memory);
}
