/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 09:47:36 by nofelten          #+#    #+#             */
/*   Updated: 2026/02/10 16:59:25 by nofelten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strndup(const char *s1, size_t size)
{
	char	*dest;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strnlen(s1, size);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
int	main(void)
{
	char	src[] = "USER=nofelten";
	char	*str;

	str = ft_strndup(src, 75874);
	printf("%s", str);
	free(str);
	return (0);
}
*/
