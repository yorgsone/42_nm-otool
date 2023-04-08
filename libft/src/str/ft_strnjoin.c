/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 15:49:01 by gemaroul          #+#    #+#             */
/*   Updated: 2018/12/23 15:49:02 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, size_t n)
{
	char	*new;
	char	*newit;
	size_t	i;

	i = 0;
	if (s1 == NULL && s2 == NULL)
		return (ft_strnew(0));
	else if (s1 == NULL)
		return (ft_strndup(s2, n));
	else if (n == 0 || s2 == NULL)
		return (ft_strdup(s1));
	new = ft_strnew(ft_strlen(s1) + n);
	if (new == NULL)
		return (NULL);
	newit = new;
	while (*s1 != '\0')
		*newit++ = *s1++;
	while (i < n && s2[i] != '\0')
		*newit++ = s2[i++];
	*newit = '\0';
	return (new);
}
