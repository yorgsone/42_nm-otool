/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 23:59:03 by gemaroul          #+#    #+#             */
/*   Updated: 2018/04/08 18:33:04 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *dst_b;
	unsigned char *src_b;

	dst_b = (unsigned char *)dst;
	src_b = (unsigned char *)src;
	while (n-- > 0)
		if ((*dst_b++ = *src_b++) == (unsigned char)c)
			return (dst_b);
	return (0);
}
