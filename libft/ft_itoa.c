/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 19:19:37 by acohaut           #+#    #+#             */
/*   Updated: 2025/11/20 12:51:19 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_itoa(char *s1, int size, int is_negative)
{
	char	*dest;
	int		i;
	int		j;

	j = 0;
	i = size - 1;
	if (is_negative)
		size = size + 1;
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	if (is_negative)
	{
		dest[j] = '-';
		j++;
	}
	while (i >= 0)
	{
		dest[j] = s1[i];
		i--;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*ft_itoa(int n)
{
	char	tab[12];
	char	*itoa;
	long	nbr;
	int		i;

	nbr = (long)n;
	i = 0;
	if (nbr == 0)
	{
		itoa = ft_strdup_itoa("0", 1, 0);
		return (itoa);
	}
	if (nbr < 0)
		nbr = -nbr;
	while (nbr > 0)
	{
		tab[i] = nbr % 10 + '0';
		nbr /= 10;
		i++;
	}
	itoa = ft_strdup_itoa(tab, i, (n < 0));
	return (itoa);
}
