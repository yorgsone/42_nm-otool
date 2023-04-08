/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 23:30:36 by gemaroul          #+#    #+#             */
/*   Updated: 2018/04/07 16:11:48 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char *s0;
	char *s10;
	char *fresh;

	s0 = (char *)s;
	if (!s || !(fresh = ft_memalloc((size_t)ft_strlen((char *)s) + 1)))
		return (NULL);
	s0 = (char *)s;
	s10 = fresh;
	while (*s0)
		*s10++ = f(*s0++);
	return (fresh);
}
