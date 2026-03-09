/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:46:19 by acohaut           #+#    #+#             */
/*   Updated: 2025/11/20 12:39:11 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printf_hexa(unsigned int nb, int uppercase)
{
	char	*base;
	char	str[9];
	int		i;

	if (nb == 0)
		return (write(1, "0", 1));
	if (uppercase)
		base = "0123456789ABCDEF";
	else if (!uppercase)
		base = "0123456789abcdef";
	i = 0;
	while (nb > 0)
	{
		str[i] = base[nb % 16];
		nb /= 16;
		i++;
	}
	str[i] = '\0';
	while (i-- > 0)
		write(1, &str[i], 1);
	return (ft_strlen(str));
}
