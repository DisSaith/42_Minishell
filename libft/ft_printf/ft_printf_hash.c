/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hash.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:46:10 by acohaut           #+#    #+#             */
/*   Updated: 2025/11/20 12:38:56 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printf_hash(va_list *args, char c)
{
	unsigned int	nb;

	nb = va_arg(*args, unsigned int);
	if (c == 'x' && nb != 0)
	{
		write(1, "0x", 2);
		return (2 + ft_printf_hexa(nb, 0));
	}
	if (c == 'X' && nb != 0)
	{
		write(1, "0X", 2);
		return (2 + ft_printf_hexa(nb, 1));
	}
	return (ft_printf_hexa(nb, 1));
}
