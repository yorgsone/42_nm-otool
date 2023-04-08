/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 00:13:56 by gemaroul          #+#    #+#             */
/*   Updated: 2018/10/30 00:13:56 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strreplace(char *str, char n, char o, int len)
{
	int i;

	if (len <= 0)
		return (str);
	i = 0;
	while (len > 0)
	{
		if (str[i] == o)
			str[i] = n;
		i++;
		len--;
	}
	return (str);
}
