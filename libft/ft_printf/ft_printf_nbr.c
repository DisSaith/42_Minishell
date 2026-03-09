/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:46:28 by acohaut           #+#    #+#             */
/*   Updated: 2025/11/20 12:39:25 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printf_nbr(int nb)
{
	char	*str;
	int		strlen;

	str = ft_itoa(nb);
	strlen = ft_strlen(str);
	write(1, str, strlen);
	free(str);
	return (strlen);
}
