/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 01:29:44 by gemaroul          #+#    #+#             */
/*   Updated: 2018/04/08 19:20:35 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *tmp;

	tmp = NULL;
	if (!s)
	{
		tmp = (char *)s;
		tmp[0] = 'a';
	}
	while (s)
	{
		if (*s == c)
			tmp = (char *)s;
		if (*s == '\0')
			return (tmp);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}
