/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strunicode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 00:14:29 by gemaroul          #+#    #+#             */
/*   Updated: 2018/10/30 00:14:30 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strunicode(wchar_t *s)
{
	int		i;
	char	*str;
	char	*tmp;
	char	*del;

	if (!s || !(str = ft_strnew(0)))
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		del = str;
		tmp = ft_convertunicode(s[i]);
		str = ft_strjoin(str, tmp);
		free(del);
		free(tmp);
		i++;
	}
	return (str);
}
