/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:15:46 by acohaut           #+#    #+#             */
/*   Updated: 2025/11/20 12:56:24 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nw_list;
	t_list	*nw_node;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	nw_list = NULL;
	while (lst)
	{
		content = f(lst->content);
		nw_node = ft_lstnew(content);
		if (!nw_node)
		{
			del(content);
			ft_lstclear(&nw_list, del);
			return (NULL);
		}
		ft_lstadd_back(&nw_list, nw_node);
		lst = lst->next;
	}
	return (nw_list);
}
