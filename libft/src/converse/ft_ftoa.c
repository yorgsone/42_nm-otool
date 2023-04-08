/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 00:04:07 by gemaroul          #+#    #+#             */
/*   Updated: 2018/10/30 00:11:51 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_ftoa(double nb, int prc)
{
	long long int	i;
	double			rnd;
	char			*str;

	str = ft_strnew(0);
	i = (long long int)nb;
	str = ft_strjoinfree(str, str, ft_itoa(i));
	str = ft_strjoinfree(str, str, ".");
	nb = nb - (double)i;
	rnd = 0.5;
	i = prc + 1;
	while (i-- != 0)
		rnd = rnd / 10;
	nb = nb + rnd;
	while (prc > 0)
	{
		nb = nb * 10;
		i = (long long int)nb;
		nb = nb - (double)i;
		str = ft_strjoinfree(str, str, ft_itoa(i));
		prc--;
	}
	return (str);
}
