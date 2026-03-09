/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 19:19:37 by acohaut           #+#    #+#             */
/*   Updated: 2025/11/20 12:38:07 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup_itoa_unsigned(char *s1, int size)
{
	char	*dest;
	int		i;
	int		j;

	j = 0;
	i = size - 1;
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	while (i >= 0)
	{
		dest[j] = s1[i];
		i--;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*ft_itoa_unsigned(unsigned int n)
{
	char			tab[12];
	char			*itoa;
	unsigned long	nbr;
	int				i;

	nbr = (unsigned long)n;
	i = 0;
	if (nbr == 0)
	{
		itoa = ft_strdup_itoa_unsigned("0", 1);
		return (itoa);
	}
	while (nbr > 0)
	{
		tab[i] = nbr % 10 + '0';
		nbr /= 10;
		i++;
	}
	itoa = ft_strdup_itoa_unsigned(tab, i);
	return (itoa);
}
