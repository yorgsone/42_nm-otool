/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 23:56:01 by gemaroul          #+#    #+#             */
/*   Updated: 2018/04/07 16:01:43 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *s0;

	if (!s || !(s0 = ft_memalloc(len + 1)))
		return (NULL);
	s0 = ft_strncpy(s0, (char *)s + start, len);
	return (s0);
}
