/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:47:01 by acohaut           #+#    #+#             */
/*   Updated: 2025/11/20 12:39:57 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printf_str(const char *str)
{
	int		strlen;

	if (!str)
		str = "(null)";
	strlen = ft_strlen(str);
	write(1, str, strlen);
	return (strlen);
}
