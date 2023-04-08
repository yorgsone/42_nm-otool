/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 05:44:02 by gemaroul          #+#    #+#             */
/*   Updated: 2018/04/09 13:37:32 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *lst;

	if ((lst = (t_list *)ft_memalloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (!content)
	{
		lst->content = NULL;
		lst->content_size = 0;
	}
	else
	{
		if ((lst->content = ft_memalloc(content_size)) == NULL)
		{
			ft_memdel((void **)&lst);
			return (NULL);
		}
		ft_memcpy((void *)lst->content, (void *)content, content_size);
		lst->content_size = content_size;
	}
	lst->next = NULL;
	return (lst);
}
