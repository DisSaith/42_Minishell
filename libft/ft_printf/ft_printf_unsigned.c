/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:47:12 by acohaut           #+#    #+#             */
/*   Updated: 2025/11/20 12:40:12 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printf_unsigned(unsigned int nb)
{
	char	*str;
	int		strlen;

	str = ft_itoa_unsigned(nb);
	strlen = ft_strlen(str);
	write(1, str, strlen);
	free(str);
	return (strlen);
}
