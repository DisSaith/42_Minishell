/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 10:39:00 by nofelten          #+#    #+#             */
/*   Updated: 2026/02/10 16:58:57 by nofelten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strnlen(const char *s, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && s[i])
		i++;
	return (i);
}
/*
int	main(void)
{
	char	str[] = "USER=nofelten";
	size_t	len = ft_strnlen(str, 6764836);
	printf("%zu", len);
	return (0);
}
*/
