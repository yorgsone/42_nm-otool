/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 00:13:47 by gemaroul          #+#    #+#             */
/*   Updated: 2018/10/30 00:13:48 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char		*ft_strmove(char *str, char blnk)
{
	int i;
	int k;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == blnk)
		{
			k = i;
			while (k > 0)
			{
				str[k] = str[k - 1];
				k--;
			}
			str[0] = blnk;
		}
		i++;
	}
	return (str);
}
