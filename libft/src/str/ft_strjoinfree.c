/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 00:13:38 by gemaroul          #+#    #+#             */
/*   Updated: 2018/10/30 00:13:39 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strjoinfree(char *ret, char *s1, char *s2)
{
	char *str;

	if (!s1 && !s2)
		return (NULL);
	str = ft_strjoin(s1, s2);
	if (ret)
		free(ret);
	return (str);
}
