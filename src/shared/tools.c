/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:34:32 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:34:33 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shared.h"

uint32_t	ft_bswap_uint32(uint32_t x)
{
	return (x & 0x000000FFU) << 24 | (x & 0x0000FF00U) << 8 |
	(x & 0x00FF0000U) >> 8 | (x & 0xFF000000U) >> 24;
}

uint64_t	ft_bswap_uint64(uint64_t x)
{
	return (x & 0x00000000000000FFUL) << 56 | (x & 0x000000000000FF00UL) << 40 |
	(x & 0x0000000000FF0000UL) << 24 | (x & 0x00000000FF000000UL) << 8 |
	(x & 0x000000FF00000000UL) >> 8 | (x & 0x0000FF0000000000UL) >> 24 |
	(x & 0x00FF000000000000UL) >> 40 | (x & 0xFF00000000000000UL) >> 56;
}

uint32_t	swap32(uint8_t big_endian, uint32_t x)
{
	if (!big_endian)
		return (ft_bswap_uint32(x));
	return (x);
}

uint64_t	swap64(uint8_t big_endian, uint64_t x)
{
	if (!big_endian)
		return (ft_bswap_uint64(x));
	return (x);
}

int32_t		ft_bswap_int32(int swap, int32_t x)
{
	if (!swap)
	{
		x = ((x << 8) & 0xFF00FF00) | ((x >> 8) & 0xFF00FF);
		return ((x << 16) | ((x >> 16) & 0xFFFF));
	}
	return (x);
}
