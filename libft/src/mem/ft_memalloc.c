/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 00:51:38 by gemaroul          #+#    #+#             */
/*   Updated: 2018/04/06 20:15:14 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_memalloc(size_t size)
{
	void *p;

	if (!(p = malloc(size)))
		return (NULL);
	ft_bzero(p, size);
	return (p);
}
