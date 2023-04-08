/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 00:12:02 by gemaroul          #+#    #+#             */
/*   Updated: 2018/10/30 00:38:15 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static char	*ft_addchar(char *str, int nb)
{
	char	*tmp;
	int		i;

	tmp = str;
	i = 0;
	while (str[i] != '\0')
		i++;
	str = (char*)malloc(sizeof(*str) * (i + 2));
	i = 0;
	str[i] = (nb > 9) ? nb + 55 : nb + 48;
	while (tmp[i] != '\0')
	{
		str[i + 1] = tmp[i];
		i++;
	}
	str[i + 1] = '\0';
	free(tmp);
	return (str);
}

char		*ft_utoa_base(unsigned long long val, int base)
{
	char		*str;

	if (base < 2 || base > 16)
		return (NULL);
	str = (char*)malloc(sizeof(*str) * 1);
	str[0] = '\0';
	while (val / base > 0)
	{
		str = ft_addchar(str, val % base);
		val = val / base;
	}
	str = ft_addchar(str, val);
	return (str);
}
