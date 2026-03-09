/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:03:08 by acohaut           #+#    #+#             */
/*   Updated: 2025/11/20 13:00:06 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	tab[12];
	long	nbr;
	size_t	i;

	nbr = (long)n;
	i = 0;
	if (nbr == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		tab[i] = nbr % 10 + '0';
		nbr /= 10;
		i++;
	}
	while (i-- > 0)
		write(fd, &tab[i], 1);
}
