/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 13:43:42 by gemaroul          #+#    #+#             */
/*   Updated: 2018/11/16 13:44:12 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

long int	ft_atol(const char *str)
{
	long int	r;
	int			sign;

	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	sign = (*str == 45) ? -1 : 1;
	(*str == 45 || *str == 43) ? str++ : str;
	r = 0;
	while (*str >= '0' && *str <= '9')
		r = r * 10 + *str++ - '0';
	return (r * sign);
}
