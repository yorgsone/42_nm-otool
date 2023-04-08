/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 00:18:58 by gemaroul          #+#    #+#             */
/*   Updated: 2018/04/06 18:44:47 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *s10;
	unsigned char *s20;

	s10 = (unsigned char *)s1;
	s20 = (unsigned char *)s2;
	if (n != 0)
	{
		while (n-- != 0)
			if (*s10++ != *s20++)
				return (*--s10 - *--s20);
	}
	return (0);
}
