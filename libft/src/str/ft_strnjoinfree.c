/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoinfree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 15:50:10 by gemaroul          #+#    #+#             */
/*   Updated: 2018/12/23 15:50:11 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strnjoinfree(char *ret, char *s1, char *s2, size_t n)
{
	char *str;

	if (!s1 && !s2)
		return (NULL);
	str = ft_strnjoin(s1, s2, n);
	if (ret)
		free(ret);
	return (str);
}
