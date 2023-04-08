/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 05:33:18 by gemaroul          #+#    #+#             */
/*   Updated: 2018/04/09 18:01:15 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *rem;
	t_list *tmp;

	rem = *alst;
	while (rem)
	{
		tmp = rem;
		ft_lstdelone(&rem, del);
		rem = tmp->next;
	}
	*alst = NULL;
}
