/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:44:02 by acohaut           #+#    #+#             */
/*   Updated: 2025/11/20 14:10:22 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_format_printf(va_list *args, char c)
{
	int	count;

	count = 0;
	if (c == '%')
		count += write(1, "%", 1);
	else if (c == 'c')
		count += ft_printf_char(va_arg(*args, int));
	else if (c == 's')
		count += ft_printf_str(va_arg(*args, const char *));
	else if (c == 'd' || c == 'i')
		count += ft_printf_nbr(va_arg(*args, int));
	else if (c == 'u')
		count += ft_printf_unsigned(va_arg(*args, unsigned int));
	else if (c == 'x')
		count += ft_printf_hexa(va_arg(*args, unsigned int), 0);
	else if (c == 'X')
		count += ft_printf_hexa(va_arg(*args, unsigned int), 1);
	else if (c == 'p')
		count += ft_printf_ptr(va_arg(*args, void *));
	return (count);
}

int	is_format(char c)
{
	if (c == '%' || c == 'c' || c == 's' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'X' || c == 'p')
		return (1);
	return (0);
}

int	is_flag(char c)
{
	if (c == '#' || c == ' ' || c == '-' || c == '+' || c == '.'
		|| c == '0' || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i] && is_format(str[i]) && !is_flag(str[i]))
				count += ft_format_printf(&args, str[i]);
			if (str[i] && !is_format(str[i]) && is_flag(str[i]))
				count += ft_flag_parsing(&args, str, &i);
		}
		else
			count += write(1, &str[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}
