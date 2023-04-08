/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 13:42:49 by gemaroul          #+#    #+#             */
/*   Updated: 2018/11/16 13:42:54 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	*ft_intndup(const int *t, int n)
{
	int *tmp;

	if (!(tmp = ft_memalloc(n)))
		return (NULL);
	ft_intcpy(tmp, t, n);
	return (tmp);
}
