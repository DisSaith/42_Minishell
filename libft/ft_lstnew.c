/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:15:54 by acohaut           #+#    #+#             */
/*   Updated: 2025/11/20 12:56:46 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nw_elem;

	nw_elem = malloc(sizeof(t_list));
	if (!nw_elem)
		return (NULL);
	nw_elem->content = content;
	nw_elem->next = NULL;
	return (nw_elem);
}
