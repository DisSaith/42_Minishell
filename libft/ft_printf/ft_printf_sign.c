/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_sign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:46:52 by acohaut           #+#    #+#             */
/*   Updated: 2025/11/20 12:39:40 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printf_sign(va_list *args, int is_plus, int is_space, char c)
{
	int		nb;

	nb = va_arg(*args, int);
	if (c == 'd' || c == 'i')
	{
		if (nb >= 0 && is_plus && !is_space)
		{
			write(1, "+", 1);
			return (1 + ft_printf_nbr(nb));
		}
		else if (nb >= 0 && !is_plus && is_space)
		{
			write(1, " ", 1);
			return (1 + ft_printf_nbr(nb));
		}
		else if (nb < 0)
			return (ft_printf_nbr(nb));
	}
	return (0);
}
