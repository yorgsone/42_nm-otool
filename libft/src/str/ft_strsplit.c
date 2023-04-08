/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 14:53:47 by gemaroul          #+#    #+#             */
/*   Updated: 2018/10/30 00:17:56 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int			ft_countwords(char const *str, char c)
{
	int count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i] != '\0')
			count++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (count);
}

char				**ft_strsplit(char const *s, char c)
{
	unsigned int	count;
	size_t			index;
	char			*begin;
	char			**tab;

	if (!s)
		return (NULL);
	count = ft_countwords(s, c);
	begin = (char *)s - 1;
	index = 0;
	if ((tab = (char **)malloc(sizeof(char *) * count + 1)) == NULL)
		return (NULL);
	while (index < count)
	{
		if (*s != c && (*(s - 1) == c || begin == s - 1))
		{
			if (!(tab[index] = ft_strnew(ft_wordlen(s, c))))
				return (NULL);
			ft_strncpy(tab[index], s, ft_wordlen(s, c));
			tab[index++][ft_wordlen(s, c)] = '\0';
		}
		s++;
	}
	tab[index] = NULL;
	return (tab);
}
