/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:46:43 by acohaut           #+#    #+#             */
/*   Updated: 2025/11/20 12:42:29 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_hexa_ptr(unsigned long long nb)
{
	char	*base;

	base = "0123456789abcdef";
	if (nb >= 16)
		ft_hexa_ptr(nb / 16);
	write(1, &base[nb % 16], 1);
}

int	ft_printf_ptr(void *address)
{
	int					count;
	unsigned long long	ptr;

	if (!address)
		return (write(1, "(nil)", 5));
	count = 0;
	count += write(1, "0x", 2);
	ptr = (unsigned long long)address;
	ft_hexa_ptr(ptr);
	while (ptr > 0)
	{
		ptr /= 16;
		count++;
	}
	return (count);
}
